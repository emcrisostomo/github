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
set(LIBGITHUB_HEADER_FILES
    src/libgithub/c/libgithub.h
    src/libgithub/c++/resources/repository.h
    src/libgithub/c++/resources/topic.h
    src/libgithub/gettext.h
    src/libgithub/gettext_defs.h
    ${PROJECT_BINARY_DIR}/config.h)

set(LIBGITHUB_SOURCE_FILES
    src/libgithub/c/libgithub.cpp
    src/libgithub/c++/resources/repository.cpp
    src/libgithub/c++/resources/topic.cpp)

set(EXTRA_LIBS ${EXTRA_LIBS} ${CURL_LIBRARIES})

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
target_link_libraries(libgithub PRIVATE ${EXTRA_LIBS})

install(TARGETS libgithub DESTINATION lib)
install(FILES ${LIBGITHUB_HEADER_FILES} DESTINATION include/libgithub)
