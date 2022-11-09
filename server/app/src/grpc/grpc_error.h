#pragma once

#include <grpcpp/support/status.h>

#include <stdexcept>

class grpc_error final : public std::runtime_error
{
public:
  grpc_error(grpc::StatusCode status, const char* msg)
    : std::runtime_error{msg}
    , m_status{status}
  {}

  [[nodiscard]] grpc::StatusCode get_status() const noexcept
  {
    return m_status;
  }

private:
  grpc::StatusCode m_status;
};

