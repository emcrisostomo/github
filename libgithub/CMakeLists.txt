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
include(FindBoost)
find_package(Boost 1.30.0 REQUIRED)

set(LIBGITHUB_HEADER_FILES
    src/libgithub/c/libgithub.h
    src/libgithub/c++/exceptions/api_error.hpp
    src/libgithub/c++/exceptions/curl_exception.hpp
    src/libgithub/c++/json/json.hpp
    src/libgithub/c++/resources/contributor.h
    src/libgithub/c++/resources/language.h
    src/libgithub/c++/resources/repository.h
    src/libgithub/c++/resources/tag.h
    src/libgithub/c++/resources/team.h
    src/libgithub/c++/resources/topic.h
    src/libgithub/c++/resources/user.h
    src/libgithub/c++/rest/rest_client.h
    src/libgithub/c++/services/repository_service.hpp
    src/libgithub/gettext.h
    src/libgithub/gettext_defs.h
    ${PROJECT_BINARY_DIR}/config.h)

set(LIBGITHUB_SOURCE_FILES
    src/libgithub/c/libgithub.cpp
    src/libgithub/c++/exceptions/api_error.cpp
    src/libgithub/c++/exceptions/curl_exception.cpp
    src/libgithub/c++/resources/contributor.cpp
    src/libgithub/c++/resources/language.cpp
    src/libgithub/c++/resources/repository.cpp
    src/libgithub/c++/resources/tag.cpp
    src/libgithub/c++/resources/team.cpp
    src/libgithub/c++/resources/topic.cpp
    src/libgithub/c++/resources/user.cpp
    src/libgithub/c++/rest/rest_client.cpp
    src/libgithub/c++/services/repository_service.cpp)

add_library(libgithub ${LIBGITHUB_SOURCE_FILES} ${LIBGITHUB_HEADER_FILES})
set_target_properties(libgithub PROPERTIES PREFIX "")

# check for gettext and libintl
if (USE_NLS)
  if (Intl_LIBRARIES)
    target_include_directories(libgithub PRIVATE ${Intl_INCLUDE_DIRS})
    target_link_libraries(libgithub PRIVATE ${Intl_LIBRARIES})
  endif ()
endif ()

target_include_directories(libgithub PRIVATE ..)
target_include_directories(libgithub PUBLIC src)
target_include_directories(libgithub PRIVATE ${PROJECT_BINARY_DIR})
# This should use the imported target Boost::boost but it's not working
target_include_directories(libgithub PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(libgithub PRIVATE CURL::libcurl)

install(TARGETS libgithub DESTINATION lib)
install(FILES ${LIBGITHUB_HEADER_FILES} DESTINATION include/libgithub)
