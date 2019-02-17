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

#ifndef GITHUB_REPOSITORY_H
#define GITHUB_REPOSITORY_H

#include <string>
#include <vector>
#include "contributor.h"
#include "language.h"
#include "user.h"
#include "tag.h"
#include "team.h"
#include "topic.h"

namespace github
{
  // TODO: add missing attributes
  class repository
  {
  public:
    static std::vector<repository> list();
    static std::vector<repository> list(std::string user);
    static std::vector<repository> list_public();

  public:
    std::vector<repository> create();
    void destroy();
    std::vector<contributor> get_contributors();
    std::vector<language> get_languages();
    std::vector<tag> get_tags();
    std::vector<team> get_team();
    std::vector<topic> get_topics();
    void set_topics(std::vector<topic> topics);
    void transfer(std::string user, std::vector<unsigned int> team_ids);

    uint64_t id;
    std::string node_id;
    std::string name;
    std::string full_name;
    github::user owner;
    bool private_repo;
    std::string html_url;
    std::string description;
    bool fork;
    std::string url;
    std::string archive_url;
    std::string assignees_url;
    std::string blobs_url;
    std::string branches_url;
    std::string collaborators_url;
    std::string comments_url;
    std::string commits_url;
    std::string compare_url;
    std::string contents_url;
    std::string contributors_url;
    std::string deployments_url;
    std::string downloads_url;
    std::string events_url;
    std::string forks_url;
    std::string git_commits_url;
    std::string git_refs_url;
    std::string git_tags_url;
    std::string git_url;
    std::string issue_comment_url;
    std::string issue_events_url;
    std::string issues_url;
    std::string keys_url;
    std::string labels_url;
    std::string languages_url;
    std::string merges_url;
    std::string milestones_url;
    std::string notifications_url;
    std::string pulls_url;
    std::string releases_url;
    std::string ssh_url;
    std::string stargazers_url;
    std::string statuses_url;
    std::string subscribers_url;
    std::string subscription_url;
    std::string tags_url;
    std::string teams_url;
    std::string trees_url;
    std::string clone_url;
    std::string mirror_url;
    std::string hooks_url;
    std::string svn_url;
    std::string homepage;
    std::string repo_language;
    uint64_t forks_count;
    uint64_t stargazers_count;
    uint64_t watchers_count;
    uint64_t size;
    std::string default_branch;
    uint64_t open_issues_count;
    std::vector<std::string> topics;
    bool has_issues;
    bool has_projects;
    bool has_wiki;
    bool has_pages;
    bool has_downloads;
    bool archived;
    // TODO: refactor to dates
    std::string pushed_at;
    std::string created_at;
    std::string updated_at;
    // TODO: model permissions
    // std::vector<permission> permissions;
    uint64_t subscribers_count;
    uint64_t network_count;
    // TODO: model license
    // github::license license;
  };
};

#endif //GITHUB_REPOSITORY_H
