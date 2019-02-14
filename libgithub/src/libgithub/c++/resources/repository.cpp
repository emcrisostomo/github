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
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "../exceptions/curl_exception.hpp"

size_t read_response_body(char *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *) userp)->append(contents, size * nmemb);
  return size * nmemb;
}

std::vector<github::repository> github::repository::list()
{
  curl_global_init(CURL_GLOBAL_ALL);

  CURL *curl_handle = curl_easy_init();
  char err_buffer[CURL_ERROR_SIZE]{};
  std::string body;

  curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, err_buffer);
  curl_easy_setopt(curl_handle, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
  curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://api.github.com/user/repos");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, read_response_body);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &body);

  struct curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Accept: application/vnd.github.v3+json");
  headers = curl_slist_append(headers, "cache-control: no-cache");
  headers = curl_slist_append(headers, "User-Agent: github C/CPP library");
//  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

  CURLcode res = curl_easy_perform(curl_handle);

  if (!(res == CURLE_OK))
  {
    throw github::curl_exception(res, err_buffer);
  }

  long response_code;
  curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
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

  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return std::vector<github::repository>();
}
