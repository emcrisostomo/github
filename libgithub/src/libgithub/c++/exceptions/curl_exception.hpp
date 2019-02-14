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
/**
 * @file
 * @brief Base exception of the `libcurl` library.
 *
 * @copyright Copyright (c) 2019 Enrico M. Crisostomo
 * @license GNU General Public License v. 3.0
 * @author Enrico M. Crisostomo
 * @version 0.0.1
 */

#ifndef CURL_EXCEPTION_H
#  define CURL_EXCEPTION_H

#  include <exception>
#  include <string>
#  include <curl/curl.h>

namespace github
{
  /**
   * @brief Base exception of the `libfswatch` library.
   *
   * An instance of this class stores an error message and an integer error
   * code.
   */
  class curl_exception : public std::exception
  {
  public:
    /**
     * @brief Constructs an exception with the specified @p code.
     *
     * @param code The error code.
     */
    explicit curl_exception(CURLcode code);

    /**
     * @brief Constructs an exception with the specified @p code.
     *
     * @param code The error code.
     */
    curl_exception(CURLcode code, std::string message);

    curl_exception(const curl_exception &other) noexcept;

    curl_exception &operator=(const curl_exception &) noexcept;

    /**
     * @brief Gets the error message.
     *
     * @return The error message.
     */
    const char *what() const noexcept override;

    /**
     * @brief Gets the error code.
     *
     * @return The error code.
     */
    virtual CURLcode get_code() const noexcept;

    /**
     * @brief Destructs an instance of this class.
     */
    ~curl_exception() noexcept override;

    /**
     * @brief Gets the error code.
     */
    explicit operator CURLcode() const noexcept;

  private:
    CURLcode code;
    std::string message;
  };
}

#endif  /* CURL_EXCEPTION_H */
