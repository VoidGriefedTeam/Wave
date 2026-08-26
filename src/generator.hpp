#pragma once

#include <pch.hpp>
#include <regex>

void generate_code(const dat& config);

std::string replace_exact_key(
    std::string instruction,
    const std::string& key,
    const std::string& value
);