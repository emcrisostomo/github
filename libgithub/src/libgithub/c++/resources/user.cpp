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
  u.login = json_value[""].GetString();
  u.id = json_value[""].GetUint64();
  u.node_id = json_value[""].GetString();
  u.avatar_url = json_value[""].GetString();
  u.gravatar_id = json_value[""].GetString();
  u.url = json_value[""].GetString();
  u.html_url = json_value[""].GetString();
  u.followers_url = json_value[""].GetString();
  u.following_url = json_value[""].GetString();
  u.gists_url = json_value[""].GetString();
  u.starred_url = json_value[""].GetString();
  u.subscriptions_url = json_value[""].GetString();
  u.organizations_url = json_value[""].GetString();
  u.repos_url = json_value[""].GetString();
  u.events_url = json_value[""].GetString();
  u.received_events_url = json_value[""].GetString();
  u.type = json_value[""].GetString();
  u.site_admin = json_value[""].GetBool();
  u.name = json_value[""].GetString();
  u.company = json_value[""].GetString();
  u.blog = json_value[""].GetString();
  u.location = json_value[""].GetString();
  u.email = json_value[""].GetString();
  u.hireable = json_value[""].GetBool();
  u.bio = json_value[""].GetString();
  u.public_repos = json_value[""].GetUint64();
  u.public_gists = json_value[""].GetUint64();
  u.followers = json_value[""].GetUint64();
  u.following = json_value[""].GetUint64();
  u.created_at = json_value[""].GetString();
  u.updated_at = json_value[""].GetString();
  u.private_gists = json_value[""].GetUint64();
  u.total_private_repos = json_value[""].GetUint64();
  u.owned_private_repos = json_value[""].GetUint64();
  u.disk_usage = json_value[""].GetUint64();
  u.collaborators = json_value[""].GetUint64();
  u.two_factor_authentication = json_value[""].GetBool();

  return u;
}
