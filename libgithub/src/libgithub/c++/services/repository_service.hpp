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

#ifndef GITHUB_REPOSITORY_SERVICE_H
#define GITHUB_REPOSITORY_SERVICE_H

#include <vector>
#include "../resources/repository.h"

namespace github
{
  class repository_service
  {
  public:
    std::vector<repository> list() const;
    std::vector<repository> list(const std::string& user) const;
    std::vector<repository> list_public() const;
    std::vector<repository> create();
    void destroy();
    void transfer(std::string user, std::vector<unsigned int> team_ids);
  };
};

#endif //GITHUB_REPOSITORY_SERVICE_H
