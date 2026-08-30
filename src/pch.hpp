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

#pragma once
#include <glaze/json.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <glaze/glaze.hpp>

struct dat
{
    std::vector<std::string> code;
    std::unordered_map<std::string, std::string> data;
    std::vector<std::string> import;
};