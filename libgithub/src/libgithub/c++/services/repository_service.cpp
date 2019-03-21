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

#include "repository_service.hpp"
#include "../rest/rest_client.h"
#include "../json/json.hpp"

namespace github
{
  static
  repository
  parse_repo(const rapidjson::Value& r)
  {
    github::repository repo;

    repo.id = r["id"].GetUint64();
    repo.node_id = r["node_id"].GetString();
    repo.name = r["name"].GetString();
    repo.full_name = r["full_name"].GetString();
    repo.owner = user::parse(r["owner"]);
    repo.private_repo = r["private"].GetBool();
    repo.html_url = r["html_url"].GetString();
    repo.description = json::json_optional_value<std::string>(r, "description");
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
    repo.mirror_url = json::json_optional_value<std::string>(r, "mirror_url");
    repo.hooks_url = r["hooks_url"].GetString();
    repo.svn_url = r["svn_url"].GetString();
    repo.homepage = json::json_optional_value<std::string>(r, "homepage");
    repo.repo_language = json::json_optional_value<std::string>(r, "language");
    repo.forks_count = r["forks_count"].GetUint64();
    repo.stargazers_count = r["stargazers_count"].GetUint64();
    repo.watchers_count = r["watchers_count"].GetUint64();
    repo.size = r["size"].GetUint64();
    repo.default_branch = r["default_branch"].GetString();
    repo.open_issues_count = r["open_issues_count"].GetUint64();
//       repo.topics = r["topics"].GetString();
    repo.has_issues = r["has_issues"].GetBool();
    repo.has_projects = r["has_projects"].GetBool();
    repo.has_wiki = r["has_wiki"].GetBool();
    repo.has_pages = r["has_pages"].GetBool();
    repo.has_downloads = r["has_downloads"].GetBool();
    repo.archived = r["archived"].GetBool();
    repo.pushed_at = r["pushed_at"].GetString();
    repo.created_at = r["created_at"].GetString();
    repo.updated_at = r["updated_at"].GetString();
//      repo.permissions = r["permissions"].GetString();
    repo.subscribers_count = json::json_optional_value<uint64_t>(r, "subscribers_count");
    repo.network_count = json::json_optional_value<uint64_t>(r, "network_count");
//      repo.license = r["license"].GetString();

    return repo;
  }

  static
  std::vector<repository>
  from_api(const std::vector<rapidjson::Document>& documents)
  {
    std::vector<github::repository> repositories;

    for (const auto& doc : documents)
    {
      for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
      {
        repositories.push_back(parse_repo(doc[i]));
      }
    }

    return repositories;
  }

  std::vector<repository>
  repository_service::list(const std::string& user) const
  {
    github::rest_client rest;
    rest.get_all_pages("https://api.github.com/users/" + user + "/repos");
    std::vector<rapidjson::Document> documents = rest.get_paginated_bodies_as_json();

    return from_api(documents);
  }

  std::vector<repository>
  repository_service::list() const
  {
    github::rest_client rest;
    rest.get_all_pages("https://api.github.com/user/repos");
    std::vector<rapidjson::Document> documents = rest.get_paginated_bodies_as_json();

    return from_api(documents);
  }

  std::vector<repository>
  repository_service::list_public() const
  {
    github::rest_client rest;
    // TODO: this call should be paginated externally
    rest.get("https://api.github.com/repositories");
    std::vector<rapidjson::Document> documents = rest.get_paginated_bodies_as_json();

    return from_api(documents);
  }
}