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

#ifndef GITHUB_USER_H
#define GITHUB_USER_H

#include <string>
#include "rapidjson/document.h"
#include <boost/optional.hpp>

namespace github
{
  // TODO: add missing attributes
  class user
  {
  public:
    std::string login;
    uint64_t id;
    std::string node_id;
    std::string avatar_url;
    std::string gravatar_id;
    std::string url;
    std::string html_url;
    std::string followers_url;
    std::string following_url;
    std::string gists_url;
    std::string starred_url;
    std::string subscriptions_url;
    std::string organizations_url;
    std::string repos_url;
    std::string events_url;
    std::string received_events_url;
    std::string type;
    bool site_admin;
    boost::optional<std::string> name;
    boost::optional<std::string> company;
    boost::optional<std::string> blog;
    boost::optional<std::string> location;
    boost::optional<std::string> email;
    boost::optional<bool> hireable;
    boost::optional<std::string> bio;
    boost::optional<uint64_t> public_repos;
    boost::optional<uint64_t> public_gists;
    boost::optional<uint64_t> followers;
    boost::optional<uint64_t> following;
    boost::optional<std::string> created_at;
    boost::optional<std::string> updated_at;
    boost::optional<uint64_t> private_gists;
    boost::optional<uint64_t> total_private_repos;
    boost::optional<uint64_t> owned_private_repos;
    boost::optional<uint64_t> disk_usage;
    boost::optional<uint64_t> collaborators;
    boost::optional<bool> two_factor_authentication;
//    boost::optional<std::string> plan;

    static user parse(const rapidjson::Value& json_value);
  };
};

#endif //GITHUB_USER_H
