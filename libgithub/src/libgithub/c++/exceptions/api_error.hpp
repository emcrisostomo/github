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
 * @brief API error of the `libcurl` library.
 *
 * @copyright Copyright (c) 2019 Enrico M. Crisostomo
 * @license GNU General Public License v. 3.0
 * @author Enrico M. Crisostomo
 * @version 0.0.1
 */

#ifndef API_ERROR_EXCEPTION_H
#  define API_ERROR_EXCEPTION_H

#  include <exception>
#  include <string>

namespace github
{
  /**
   * @brief Base exception of the `libgithub` library.
   *
   * An instance of this class stores an error message and an integer error
   * code.
   */
  class api_error : public std::exception
  {
  public:
    /**
     * @brief Constructs an exception with the specified @p status code.
     *
     * @param code The status code.
     */
    explicit api_error(unsigned long status_code);

    /**
     * @brief Constructs an exception with the specified @p code.
     *
     * @param code The error code.
     */
    api_error(unsigned long status_code, std::string message);

    api_error(const api_error &other) noexcept;

    api_error &operator=(const api_error &) noexcept;

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
    virtual unsigned long get_status_code() const noexcept;

    /**
     * @brief Destructs an instance of this class.
     */
    ~api_error() noexcept override;

    /**
     * @brief Gets the error code.
     */
    explicit operator unsigned long() const noexcept;

  private:
    unsigned long status_code;
    std::string message;
  };
}

#endif  // API_ERROR_EXCEPTION_H
