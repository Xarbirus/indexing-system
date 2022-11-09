#pragma once

#include <chrono>
#include <string>

std::string to_user_string(const std::chrono::system_clock::duration& duration);
