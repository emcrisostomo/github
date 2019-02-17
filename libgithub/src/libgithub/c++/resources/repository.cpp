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
  std::vector<rapidjson::Document> documents = rest.get_paginated_bodies_as_json();

  std::vector<github::repository> repositories;
  for (const auto& doc : documents)
  {
    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
    {
      github::repository repo;
      const rapidjson::Value& r = doc[i];
      repo.id = r["id"].GetUint64();
      repo.node_id = r["node_id"].GetString();
      repo.name = r["name"].GetString();
      repo.full_name = r["full_name"].GetString();
// "owner": {
//      "login": "octocat",
//      "id": 1,
//      "node_id": "MDQ6VXNlcjE=",
//      "avatar_url": "https://github.com/images/error/octocat_happy.gif",
//      "gravatar_id": "",
//      "url": "https://api.github.com/users/octocat",
//      "html_url": "https://github.com/octocat",
//      "followers_url": "https://api.github.com/users/octocat/followers",
//      "following_url": "https://api.github.com/users/octocat/following{/other_user}",
//      "gists_url": "https://api.github.com/users/octocat/gists{/gist_id}",
//      "starred_url": "https://api.github.com/users/octocat/starred{/owner}{/repo}",
//      "subscriptions_url": "https://api.github.com/users/octocat/subscriptions",
//      "organizations_url": "https://api.github.com/users/octocat/orgs",
//      "repos_url": "https://api.github.com/users/octocat/repos",
//      "events_url": "https://api.github.com/users/octocat/events{/privacy}",
//      "received_events_url": "https://api.github.com/users/octocat/received_events",
//      "type": "User",
//      "site_admin": false
//    },
      repo.private_repo = r["private"].GetBool();
      repo.html_url = r["html_url"].GetString();
      repo.description = r["description"].GetString();
      repo.fork = r["fork"].GetBool();
      repo.url = r["url"].GetString();
      repo.archive_url = r["archive_url"].GetString();
      repo.assignees_url = r["assignees_url"].GetString();
      repo.blobs_url = r["blobs_url"].GetString();
      repo.branches_url = r["branches_url"].GetString();
      repo.collaborators_url = r["collaborators_url"].GetString();
      repo.comments_url = r["comments_url"].GetString();
      repo.commits_url = r["commits_url"].GetString();
      repo.compare_url = r["compare_url"].GetString();
      repo.contents_url = r["contents_url"].GetString();
      repo.contributors_url = r["contributors_url"].GetString();
      repo.deployments_url = r["deployments_url"].GetString();
      repo.downloads_url = r["downloads_url"].GetString();
      repo.events_url = r["events_url"].GetString();
      repo.forks_url = r["forks_url"].GetString();
      repo.git_commits_url = r["git_commits_url"].GetString();
      repo.git_refs_url = r["git_refs_url"].GetString();
      repo.git_tags_url = r["git_tags_url"].GetString();
      repo.git_url = r["git_url"].GetString();
      repo.issue_comment_url = r["issue_comment_url"].GetString();
      repo.issue_events_url = r["issue_events_url"].GetString();
      repo.issues_url = r["issues_url"].GetString();
      repo.keys_url = r["keys_url"].GetString();
      repo.labels_url = r["labels_url"].GetString();
      repo.languages_url = r["languages_url"].GetString();
      repo.merges_url = r["merges_url"].GetString();
      repo.milestones_url = r["milestones_url"].GetString();
      repo.notifications_url = r["notifications_url"].GetString();
      repo.pulls_url = r["pulls_url"].GetString();
      repo.releases_url = r["releases_url"].GetString();
      repo.ssh_url = r["ssh_url"].GetString();
      repo.stargazers_url = r["stargazers_url"].GetString();
      repo.statuses_url = r["statuses_url"].GetString();
      repo.subscribers_url = r["subscribers_url"].GetString();
      repo.subscription_url = r["subscription_url"].GetString();
      repo.tags_url = r["tags_url"].GetString();
      repo.teams_url = r["teams_url"].GetString();
      repo.trees_url = r["trees_url"].GetString();
      repo.clone_url = r["clone_url"].GetString();
      repo.mirror_url = r["mirror_url"].GetString();
      repo.hooks_url = r["hooks_url"].GetString();
      repo.svn_url = r["svn_url"].GetString();
      repo.homepage = r["homepage"].GetString();

//    "language": null,
//    "forks_count": 9,
//    "stargazers_count": 80,
//    "watchers_count": 80,
//    "size": 108,
//    "default_branch": "master",
//    "open_issues_count": 0,
//    "topics": [
//      "octocat",
//      "atom",
//      "electron",
//      "API"
//    ],
//    "has_issues": true,
//    "has_projects": true,
//    "has_wiki": true,
//    "has_pages": false,
//    "has_downloads": true,
//    "archived": false,
//    "pushed_at": "2011-01-26T19:06:43Z",
//    "created_at": "2011-01-26T19:01:12Z",
//    "updated_at": "2011-01-26T19:14:43Z",
//    "permissions": {
//      "admin": false,
//      "push": false,
//      "pull": true
//    },
//    "subscribers_count": 42,
//    "network_count": 0,
//    "license": {
//      "key": "mit",
//      "name": "MIT License",
//      "spdx_id": "MIT",
//      "url": "https://api.github.com/licenses/mit",
//      "node_id": "MDc6TGljZW5zZW1pdA=="
//    }
      std::cerr << repo.full_name << "\n";
      repositories.push_back(std::move(repo));
    }
  }

  return std::vector<github::repository>();
}
