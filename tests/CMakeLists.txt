#
# Copyright (c) 2019 Enrico M. Crisostomo
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 3, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
include(CTest)

link_libraries(libgithub)

add_executable(repo-list repo-list.cpp)
add_executable(repo-list-user repo-list-user.cpp)
add_executable(repo-list-public repo-list-public.cpp)

add_test(repo-list repo-list)
set_tests_properties(repo-list PROPERTIES PASS_REGULAR_EXPRESSION "^$")
add_test(repo-list-user repo-list-user)
set_tests_properties(repo-list-user PROPERTIES PASS_REGULAR_EXPRESSION "^$")
add_test(repo-list-public repo-list-public)
set_tests_properties(repo-list-public PROPERTIES PASS_REGULAR_EXPRESSION "^$")
