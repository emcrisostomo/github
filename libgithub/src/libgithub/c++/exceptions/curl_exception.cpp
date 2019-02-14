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
#include "curl_exception.hpp"

#include <utility>
#include "../../gettext_defs.h"

namespace github
{
  curl_exception::curl_exception(CURLcode code) :
      code(code)
  {
  }

  curl_exception::curl_exception(CURLcode code, std::string message) :
      code(code), message(std::move(message))
  {
  }

  const char *curl_exception::what() const noexcept
  {
    std::string error(curl_easy_strerror(code));

    if (message.length() > 0)
    {
      error += "\n";
      error += message;
    }

    return error.c_str();
  }

  CURLcode curl_exception::get_code() const noexcept
  {
    return code;
  }

  curl_exception::operator CURLcode() const noexcept
  {
    return code;
  }

  curl_exception::~curl_exception() noexcept = default;

  curl_exception::curl_exception(const curl_exception &other) noexcept :
      code(other.code), message(other.message)
  {
  }

  curl_exception &curl_exception::operator=(const curl_exception &that) noexcept
  {
    if (&that == this)
      return *this;

    this->code = that.code;
    this->message = that.message;

    return *this;
  }
}
