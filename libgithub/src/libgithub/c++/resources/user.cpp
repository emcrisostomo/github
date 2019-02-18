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
#include "rapidjson/document.h"


github::user github::user::parse(const rapidjson::Value& json_value)
{
  // TODO: fix parsing code
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
  const rapidjson::Value::ConstMemberIterator& name_value = json_value.FindMember("name");
  if (name_value != json_value.MemberEnd())
    u.name = name_value->value.GetString();
  u.company = json_value["company"].GetString();
  u.blog = json_value["blog"].GetString();
  u.location = json_value["location"].GetString();
  u.email = json_value["email"].GetString();
  u.hireable = json_value["hireable"].GetBool();
  u.bio = json_value["bio"].GetString();
  u.public_repos = json_value["public_repos"].GetUint64();
  u.public_gists = json_value["public_gists"].GetUint64();
  u.followers = json_value["followers"].GetUint64();
  u.following = json_value["following"].GetUint64();
  u.created_at = json_value["created_at"].GetString();
  u.updated_at = json_value["updated_at"].GetString();
  u.private_gists = json_value["private_gists"].GetUint64();
  u.total_private_repos = json_value["total_private_repos"].GetUint64();
  u.owned_private_repos = json_value["owned_private_repos"].GetUint64();
  u.disk_usage = json_value["disk_usage"].GetUint64();
  u.collaborators = json_value["collaborators"].GetUint64();
  u.two_factor_authentication = json_value["two_factor_authentication"].GetBool();

  return u;
}
