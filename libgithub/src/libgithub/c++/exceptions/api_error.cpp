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
#include "api_error.hpp"

#include <utility>
#include "../../gettext_defs.h"

namespace github
{
  api_error::api_error(unsigned long status_code) :
      status_code(status_code)
  {
  }

  api_error::api_error(unsigned long status_code, std::string message) :
      status_code(status_code), message(std::move(message))
  {
  }

  const char *api_error::what() const noexcept
  {
    return message.c_str();
  }

  unsigned long api_error::get_status_code() const noexcept
  {
    return status_code;
  }

  api_error::operator unsigned long() const noexcept
  {
    return status_code;
  }

  api_error::~api_error() noexcept = default;

  api_error::api_error(const api_error &other) noexcept :
      status_code(other.status_code), message(other.message)
  {
  }

  api_error &api_error::operator=(const api_error &that) noexcept
  {
    if (&that == this)
      return *this;

    this->status_code = that.status_code;
    this->message = that.message;

    return *this;
  }
}
