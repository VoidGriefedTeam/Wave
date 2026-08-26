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

#include <generator.hpp>

std::string replace_exact_key(
    std::string instruction,
    const std::string& key,
    const std::string& value)
{
    std::regex key_pattern("\\b" + key + "\\b");

    return std::regex_replace(instruction, key_pattern, value);
}

void generate_code(const dat& config)
{
    std::string instruction;
    std::string key;
    std::string real_value;
    std::vector<std::string> keys;
    std::vector<std::string> values;
    int index = 0;

    for (const auto& entry : config.data)
    {
        keys.push_back(entry.first);
        values.push_back(entry.second);
    }
    
    instruction = config.code[index];
    key = keys[index];
    real_value = values[index];
    std::string final_code = replace_exact_key(instruction, key, real_value);

    std::ofstream file("output.cpp");
    file << "#include " << config.import[index] << "\n";
    file << "int main() {\n";
    file << final_code << "\n";
    file << "}\n";
    file.close();
}