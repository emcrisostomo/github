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

#ifndef GITHUB_JSON_H
#define GITHUB_JSON_H

namespace github
{
  namespace json
  {
    template<typename T>
    bool json_has_field(const rapidjson::Value& json, const char *name)
    {
      const auto itr = json.FindMember(name);
      return !(itr == json.MemberEnd() || itr->value.IsNull());
    }

    template<typename T>
    boost::optional<T>
    json_optional_value(const rapidjson::Value& json,
                        const char *name)
    {
      if (!json_has_field<T>(json, name)) return boost::optional<T>();

      return boost::optional<T>(json[name].Get<T>());
    }

    template<>
    inline
    boost::optional<std::string>
    json_optional_value(const rapidjson::Value& json,
                        const char *name)
    {
      if (!json_has_field<std::string>(json, name)) return boost::optional<std::string>();

      return boost::optional<std::string>(json[name].GetString());
    }
  }
}

#endif //GITHUB_JSON_H
