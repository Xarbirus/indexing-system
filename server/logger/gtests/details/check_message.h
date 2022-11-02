#pragma once

#include <spdlog/details/log_msg.h>

void check(const spdlog::details::log_msg& message, std::string_view master_value);
