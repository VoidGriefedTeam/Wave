// Copyright © 2026  voidgriefedteam

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>
#include <translator.hpp>

std::string replace_exact_key(
    std::string instruction,
    const std::string& key,
    const std::string& value)
{
    std::regex key_pattern("\\b" + key + "\\b");

    return std::regex_replace(instruction, key_pattern, value);
}

struct Function
{
    std::string import;
    std::string code;
    std::vector<std::string> data;
};

using Config = std::map<std::string, Function>;

Config config;

auto ec = glz::read_file_json(
    config,
    "cpp_dic/dic.json",
    std::string{}
);


ret translate(const extdat& data)
{
    std::vector<std::string> imp;
    std::vector<std::string> code;
    for (size_t i = 0; i < data.keywords.size(); i++)
    {
        std::string imports = "#include " + config[data.keywords[i]].import;
        std::string codes = config[data.keywords[i]].code;
        imp.push_back(imports);
        std::string cod;
        cod = replace_exact_key(codes, config[data.keywords[i]].data[0], data.values[i]);
        code.push_back(cod);
       
    }
    ret result;
    result.imp = imp;
    result.code = code;
    return result;
}