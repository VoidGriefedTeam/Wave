// Copyright © 2026  VoidGriefedTeam

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

std::vector<std::string> removeDuplicates(std::vector<std::string> vec)
{
    std::vector<std::string> result;

    for (int i = 0; i < vec.size(); i++)
    {
        if (std::find(result.begin(), result.end(), vec[i]) == result.end())
        {
            result.push_back(vec[i]);
        }
    }

    return result;
}

void generate_code(const ret& translated, const std::string& output)
{
    
    std::fstream file(output, std::ios::out | std::ios::trunc);

    std::vector<std::string> imps = removeDuplicates(translated.imp); 

    for (int i = 0; i < imps.size(); i++)
    {
        file << imps[i] << "\n";
    }

    file << "int main() {\n";

    for (int b = 0; b < translated.code.size(); b++)
    {
        file << translated.code[b] << "\n";
    }
    file << "}\n"; 
}