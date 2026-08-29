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

#pragma once
# include <pch.hpp>

inline std::string function;
inline std::string value;

struct extdat 
{
    std::vector <std::string> values;
    std::vector <std::string> keywords;
};

std::vector<std::string> parse(std::ifstream& file);
extdat extract(const std::vector<std::string>& words);