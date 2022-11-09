#pragma once

#include "app/src/grpc/grpc_error.h"

#include <functional>

template<typename Implementation>
class grpc_call_processor
{
public:
  template<typename Fcn, typename Request, typename Response>
  grpc::Status process(const Fcn& callback, const Request& request, Response& response)
  {
    try
    {
      response = std::invoke(callback, impl(), request);
    }
    catch(const grpc_error& ex)
    {
      return {ex.get_status(), ex.what()};
    }
    catch(const std::exception& ex)
    {
      return {grpc::StatusCode::UNKNOWN, ex.what()};
    }
    catch(...)
    {
      return {grpc::StatusCode::UNKNOWN, "Unknown object was thrown"};
    }
    return {};
  }

private:
  Implementation* impl()
  {
    return static_cast<Implementation*>(this);
  }
};
