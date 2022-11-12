#pragma once

#include <string>
#include <vector>

[[nodiscard]] std::pair<std::string, std::string> separate_first_word(std::string_view str);

[[nodiscard]] std::pair<std::string, std::string> prepare_command(std::string str);
