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

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: main.exe <file.wave>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Could not open: " << argv[1] << '\n';
        return 1;
    }
    parse(file);
}