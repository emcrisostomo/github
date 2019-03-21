/*
 * Copyright (c) 2019 Enrico M. Crisostomo
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rest_client.h"
#include "../exceptions/api_error.hpp"
#include "../exceptions/curl_exception.hpp"
#include <map>
#include <regex>

namespace github
{
static void curl_deleter(CURL *curl)
{
  curl_easy_cleanup(curl);
}

static std::string get_next_url(const std::vector<std::string>& links)
{
  // A link header has this structure:
  //
  //   <https://api.github.com/user/repos?page=2>; rel="next"
  std::string link_relation_grammar = R"EOL(<([^>]*)>; *rel="([^"]*)")EOL";
  std::regex link_regex(link_relation_grammar, std::regex_constants::extended);

  for (const auto& link : links)
  {
    std::smatch fragments;

    if (!std::regex_match(link, fragments, link_regex))
    {
      throw std::runtime_error("Failed to parse link fragment");
    }

    if (fragments[2].compare("next") == 0)
    {
      return fragments[1];
    }
  }

  return "";
}

static std::vector<std::string> get_links(const std::string& link_header)
{
  std::vector<std::string> links;
  std::string current_link_fragment = link_header;

  while (!current_link_fragment.empty())
  {
    std::string link_relation_grammar = R"EOL((<[^>]*>; *rel="[^"]*"))EOL";
    std::string regex_text = "^" + link_relation_grammar + "( *, *(.*))?";
    std::regex link_relations_regex(regex_text, std::regex_constants::extended);

    std::smatch fragments;

    if (std::regex_match(current_link_fragment, fragments, link_relations_regex))
    {
      links.push_back(fragments[1]);

      if (fragments.size() == 4)
        current_link_fragment = fragments[3];
      else
        current_link_fragment = {};
    }
    else
    {
      // TODO: add error management
      current_link_fragment = {};
    }
  }

  return links;
}

static size_t read_response_body(char *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *) userp)->append(contents, size * nmemb);
  return size * nmemb;
}

static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
  size_t total = nitems * size;

  if (userdata == nullptr) return total;

  /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
  /* 'userdata' is set with CURLOPT_HEADERDATA */
  char res[total + 1];
  strncpy(res, buffer, total);
  res[total] = '\0';

  std::string header(res);
  std::string::size_type pos;
  pos = header.find(": ");

  if (pos == std::string::npos) return total;

  std::string header_name = header.substr(0, pos);
  // TODO: HTTP headers should end with \r\n but may end with \n: removing two characters
  std::string header_value = header.substr(pos + 2, header.length() - pos - 2 - 2);

  auto *header_map = (std::map<std::string, std::string> *) userdata;
  (*header_map)[header_name] = header_value;

  return total;
}

rest_client::rest_client()
{
  curl_global_init(CURL_GLOBAL_ALL);
  curl = std::unique_ptr<CURL, std::function<void(CURL *)>>(curl_easy_init(), curl_deleter);

  set_common_opts();
}

rest_client::~rest_client()
{
  curl_global_cleanup();
}

void rest_client::cleanup_pre_call()
{
  err_buffer[0] = '\0';
  body = "";
  header_map.clear();
}

void rest_client::set_common_opts()
{
  // @formatter:off
    curl_easy_setopt(curl.get(), CURLOPT_NETRC,          CURL_NETRC_OPTIONAL);
    curl_easy_setopt(curl.get(), CURLOPT_ERRORBUFFER,    err_buffer);
    curl_easy_setopt(curl.get(), CURLOPT_VERBOSE,        0L);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION,  read_response_body);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA,      &body);
    curl_easy_setopt(curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl.get(), CURLOPT_HEADERDATA,     &header_map);
    // @formatter:on
}

CURLcode rest_client::perform_call()
{
  cleanup_pre_call();
  return curl_easy_perform(curl.get());
}

void rest_client::get(const std::string& url, bool paginated)
{
  std::string next_page_url = url;

  while (!next_page_url.empty())
  {
    // @formatter:off
      curl_easy_setopt(curl.get(), CURLOPT_CUSTOMREQUEST,  "GET");
      curl_easy_setopt(curl.get(), CURLOPT_URL,            next_page_url.c_str());
      // @formatter:on

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/vnd.github.v3+json");
    headers = curl_slist_append(headers, "cache-control: no-cache");
    headers = curl_slist_append(headers, "User-Agent: github C/CPP library");
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers);

    CURLcode res = perform_call();

    // TODO: encapsulate check
    if (!(res == CURLE_OK))
    {
      throw curl_exception(res, err_buffer);
    }

    // TODO: save response code
    unsigned long response_code;
    curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &response_code);

    // TODO: encapsulate and parametrise check
    if (response_code != 200)
    {
      throw api_error(response_code);
    }

    paginated_bodies.push_back(std::move(body));

    next_page_url = {};
    if (paginated && header_map.find("Link") != header_map.end())
    {
      std::string link_header = header_map["Link"];
      std::vector<std::string> links = get_links(link_header);
      next_page_url = get_next_url(links);
    }
  }
}

std::vector<std::string> rest_client::get_paginated_bodies() const
{
  return this->paginated_bodies;
}

std::vector<rapidjson::Document> rest_client::get_paginated_bodies_as_json() const
{
  std::vector<rapidjson::Document> documents;
  for (const auto& body : this->paginated_bodies)
  {
    // Load all documents
    {
      rapidjson::Document doc;
      doc.Parse(body.c_str());
      documents.push_back(std::move(doc));
    }
  }

  return documents;
}
};
