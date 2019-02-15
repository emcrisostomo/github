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

#include "repository.h"
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "../exceptions/curl_exception.hpp"

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
  std::string header_value = header.substr(pos + 2, header.length());

  std::cout << "Header name: " << header_name << "\n";
  std::cout << "Header value: " << header_value << "\n";

  auto *header_map = (std::map<std::string, std::string> *) userdata;
  (*header_map)[header_name] = header_value;

  return total;
}

std::vector<github::repository> github::repository::list()
{
  curl_global_init(CURL_GLOBAL_ALL);

  CURL *curl = curl_easy_init();
  char err_buffer[CURL_ERROR_SIZE]{};
  std::string body;
  std::map<std::string, std::string> header_map;

  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, err_buffer);
  curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/user/repos");
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_response_body);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_map);

  struct curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Accept: application/vnd.github.v3+json");
  headers = curl_slist_append(headers, "cache-control: no-cache");
  headers = curl_slist_append(headers, "User-Agent: github C/CPP library");
//  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  CURLcode res = curl_easy_perform(curl);

  if (!(res == CURLE_OK))
  {
    throw github::curl_exception(res, err_buffer);
  }

  long response_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  std::cerr << "Response code: " << response_code << "\n";

  std::cout << body << "\n";

  rapidjson::Document doc;
  doc.Parse(body.c_str());

  std::vector<github::repository> repositories;

  for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
  {
    github::repository repo;
    const rapidjson::Value& r = doc[i];
    repo.id = r["id"].GetUint64();
    repo.name = r["name"].GetString();
    std::cerr << repo.id << ":" << repo.name << "\n";
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return std::vector<github::repository>();
}
