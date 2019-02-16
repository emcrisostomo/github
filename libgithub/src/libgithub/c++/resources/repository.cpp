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
#include "../rest/rest_client.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <regex>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "../exceptions/curl_exception.hpp"
#include "../exceptions/api_error.hpp"

std::vector<github::repository> github::repository::list()
{
  github::rest_client rest;
  rest.get("https://api.github.com/user/repos", true);
  const auto bodies = rest.get_paginated_bodies();

  std::vector<rapidjson::Document> documents;
  for (const auto& body : bodies)
  {
    // Load all documents
    {
      rapidjson::Document doc;
      doc.Parse(body.c_str());
      documents.push_back(std::move(doc));
    }
  }

  std::vector<github::repository> repositories;
  for (const auto& doc : documents)
  {
    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
    {
      github::repository repo;
      const rapidjson::Value& r = doc[i];
      repo.id = r["id"].GetUint64();
      repo.name = r["name"].GetString();
      repo.full_name = r["full_name"].GetString();
      std::cerr << repo.full_name << "\n";
      repositories.push_back(std::move(repo));
    }
  }

  return std::vector<github::repository>();
}
