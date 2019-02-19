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

#include "user.h"
#include "libgithub/src/libgithub/c++/json/json.hpp"
#include "rapidjson/document.h"

github::user github::user::parse(const rapidjson::Value& json_value)
{
  github::user u;
  u.login = json_value["login"].GetString();
  u.id = json_value["id"].GetUint64();
  u.node_id = json_value["node_id"].GetString();
  u.avatar_url = json_value["avatar_url"].GetString();
  u.gravatar_id = json_value["gravatar_id"].GetString();
  u.url = json_value["url"].GetString();
  u.html_url = json_value["html_url"].GetString();
  u.followers_url = json_value["followers_url"].GetString();
  u.following_url = json_value["following_url"].GetString();
  u.gists_url = json_value["gists_url"].GetString();
  u.starred_url = json_value["starred_url"].GetString();
  u.subscriptions_url = json_value["subscriptions_url"].GetString();
  u.organizations_url = json_value["organizations_url"].GetString();
  u.repos_url = json_value["repos_url"].GetString();
  u.events_url = json_value["events_url"].GetString();
  u.received_events_url = json_value["received_events_url"].GetString();
  u.type = json_value["type"].GetString();
  u.site_admin = json_value["site_admin"].GetBool();
  u.name = json::json_optional_value<std::string>(json_value, "name");
  u.company = json::json_optional_value<std::string>(json_value, "company");
  u.blog = json::json_optional_value<std::string>(json_value, "blog");
  u.location = json::json_optional_value<std::string>(json_value, "location");
  u.email = json::json_optional_value<std::string>(json_value, "email");
  u.hireable = json::json_optional_value<bool>(json_value, "hireable");
  u.bio = json::json_optional_value<std::string>(json_value, "bio");
  u.public_repos = json::json_optional_value<uint64_t >(json_value, "public_repos");
  u.public_gists = json::json_optional_value<uint64_t>(json_value, "public_gists");
  u.followers = json::json_optional_value<uint64_t>(json_value, "followers");
  u.following = json::json_optional_value<uint64_t>(json_value, "following");
  u.created_at = json::json_optional_value<std::string>(json_value, "created_at");
  u.updated_at = json::json_optional_value<std::string>(json_value, "updated_at");
  u.private_gists = json::json_optional_value<uint64_t>(json_value, "private_gists");
  u.total_private_repos = json::json_optional_value<uint64_t>(json_value, "total_private_repos");
  u.owned_private_repos = json::json_optional_value<uint64_t>(json_value, "owned_private_repos");
  u.disk_usage = json::json_optional_value<uint64_t>(json_value, "disk_usage");
  u.collaborators = json::json_optional_value<uint64_t>(json_value, "collaborators");
  u.two_factor_authentication = json::json_optional_value<bool>(json_value, "two_factor_authentication");

  return u;
}
