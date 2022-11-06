#pragma once

#include <string>
#include <vector>

std::pair<std::string, std::string> separate_first_word(const std::string& str);

std::pair<std::string, std::string> prepare_command(std::string str);
