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

#ifndef GITHUB_REST_CLIENT_H
#define GITHUB_REST_CLIENT_H

#include <curl/curl.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace github
{
  void curl_deleter(CURL *curl);

  class rest_client
  {
  public:
    rest_client();
    virtual ~rest_client();

    void get(const std::string& url, bool paginated = false);
    std::vector<std::string> get_paginated_bodies() const;

  private:
    void set_common_opts();
    void cleanup_pre_call();
    CURLcode perform_call();

  private:
    std::unique_ptr<CURL, std::function<void(CURL *)>> curl;
    std::string body;
    std::map<std::string, std::string> header_map;
    std::vector<std::string> paginated_bodies;
    char err_buffer[CURL_ERROR_SIZE]{};
  };
};

#endif // GITHUB_REST_CLIENT_H
