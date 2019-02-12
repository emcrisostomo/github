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
#include "config.h"
#include "gettext.h"
#include "github.hpp"
#include "libgithub/c/libgithub.h"
#include <clocale>
#include <string>
#include <getopt.h>
#include <iostream>
#include <cstdlib>

#define _(String) gettext(String)

static bool verbose_flag = false;
static int version_flag = false;

static bool parse_optsss(int argc, char **argv);
static void usage(std::ostream& stream);
static void print_version(std::ostream& stream);

int main(int argc, char **argv)
{
  // Trigger gettext operations
#ifdef ENABLE_NLS
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);
#endif

  if (!parse_optsss(argc, argv))
    return EXIT_FAILURE;

  github_init_library();

  return 0;
}

static bool parse_optsss(int argc, char **argv)
{
  int ch;
  std::string short_options = "hv";
  int option_index = 0;
  static struct option long_options[] = {
      {"help",    no_argument, nullptr,       'h'},
      {"verbose", no_argument, nullptr,       'v'},
      {"version", no_argument, &version_flag, true},
      {nullptr, 0,             nullptr,       0}
  };

  while ((ch = getopt_long(argc,
                           argv,
                           short_options.c_str(),
                           long_options,
                           &option_index)) != -1)
  {
    switch (ch)
    {
      case 'h':
        usage(std::cout);
        return false;

      case 'v':
        verbose_flag = true;
        break;

      case '?':
        usage(std::cerr);
        return false;
    }
  }

  // Set verbose mode for libgithub.
//  gh_set_verbose(verbose_flag);

  if (version_flag)
  {
    print_version(std::cout);
    return false;
  }

  return true;
}

static void print_version(std::ostream& stream)
{
  stream << PACKAGE_STRING << "\n";
  stream << "Copyright (C) 2019 Enrico M. Crisostomo <enrico.m.crisostomo@gmail.com>.\n";
  stream << _("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
  stream << _("This is free software: you are free to change and redistribute it.\n");
  stream << _("There is NO WARRANTY, to the extent permitted by law.\n");
  stream << "\n";
  stream << _("Written by Enrico M. Crisostomo.");
  stream << "\n";
}

static void usage(std::ostream& stream)
{
  stream << PACKAGE_STRING << "\n\n";
  stream << _("Usage:\n");
  stream << PACKAGE_NAME << _(" [OPTION] ... path ...\n");
  stream << "\n";
  stream << _("Options:\n");
  stream << " -h, --help            " << _("Show this message.\n");
  stream << " -v, --verbose         " << _("Print verbose output.\n");
  stream << "     --version         " << _("Print the version of ") << PACKAGE_NAME << _(" and exit.\n");
  stream << "\n";

  stream << _("See the man page for more information.\n\n");

  stream << _("Report bugs to <") << PACKAGE_BUGREPORT << ">.\n";
  stream << PACKAGE << _(" home page: <") << PACKAGE_URL << ">.";
  stream << "\n";
}