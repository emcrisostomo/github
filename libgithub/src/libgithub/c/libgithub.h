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
 * @brief Header of the `libgithub` library.
 *
 * This header file defines the API of the `libgithub` library.
 *
 * @copyright Copyright (c) 2019 Enrico M. Crisostomo
 * @license GNU General Public License v. 3.0
 * @author Enrico M. Crisostomo
 * @version 0.0.1
 */

#ifndef LIBGITHUB_H
#define LIBGITHUB_H

#  ifdef __cplusplus
extern "C"
{
#  endif

  void github_init_library();

#  ifdef __cplusplus
}
#  endif

#endif // LIBGITHUB_H
