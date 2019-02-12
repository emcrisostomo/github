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

#include <vector>
#include "contributor.h"
#include "language.h"
#include "tag.h"
#include "team.h"
#include "topic.h"

namespace github
{
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
  };
};

#endif //GITHUB_REPOSITORY_H
