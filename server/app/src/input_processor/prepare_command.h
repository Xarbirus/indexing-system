#pragma once

#include <string>
#include <vector>

[[nodiscard]] std::pair<std::string, std::string> separate_first_word(const std::string& str);

[[nodiscard]] std::pair<std::string, std::string> prepare_command(std::string str);
