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

#include <lexer.hpp>
#include <lexer.hpp>


std::vector<std::string> parse(std::ifstream& file)
{
    std::vector<std::string> words;
    std::string word;

    while (std::getline(file, word))
        words.push_back(word);

    return words;
}

extdat extract(const std::vector<std::string>& words)
{
    extdat data;

    for (const std::string& line : words)
    {
        size_t open = 0;

        while ((open = line.find('(', open)) != std::string::npos)
        {
            size_t close = line.find(')', open + 1);

            if (close == std::string::npos)
                break;

            // Find the beginning of the keyword
            size_t start = open;

            while (start > 0 &&
                   line[start - 1] != ' ' &&
                   line[start - 1] != '\t')
            {
                start--;
            }

            // keyword INCLUDING ()
            std::string keyword = line.substr(start, open - start) + "()";
            data.keywords.push_back(keyword);

            // value INSIDE ()
            data.values.push_back(
                line.substr(open + 1, close - open - 1)
            );

            open = close + 1;
        }
    }

    return data;
}


