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

#include "config.h"
#include "libgithub.h"
#include "../gettext_defs.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

size_t read_response_body(char *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *) userp)->append(contents, size * nmemb);
  return size * nmemb;
}

void github_init_library()
{
  // Trigger gettext operations
#ifdef ENABLE_NLS
  bindtextdomain(PACKAGE, LOCALEDIR);
#endif

  curl_global_init(CURL_GLOBAL_ALL);

  CURL *curl_handle = curl_easy_init();
  std::string body;

  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.google.com/");
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, read_response_body);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &body);

  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);

  std::cout << body << std::endl;
}
