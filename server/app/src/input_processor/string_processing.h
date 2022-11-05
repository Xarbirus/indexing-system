#pragma once

#include <string_view>

constexpr auto whitespaces = " \t\n\r\v\f";

void trim(std::string_view& str);
