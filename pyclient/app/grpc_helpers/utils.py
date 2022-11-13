import functools
import grpc


class GrpcError:
    """
    A class for wrapping errors from gRPC

    Attributes
    ----------
    message : str
        error message
    """
    def __init__(self, message: str):
        self.message = message

    def __str__(self):
        return self.message


def safe_grpc_call(func):
    """
    A decorator that wraps gRPC call errors to GrpcError
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except grpc.RpcError as e:
            if e.code() == grpc.StatusCode.UNKNOWN:
                error_message = f"Error: {e.details()}"
            else:
                error_message = f"gRPC client error: {e.details()} (error code - {e.code()})"
        except Exception as e:
            error_message = f"Get error: {e})"
        except:
            error_message = f"Unknown error!"
        return GrpcError(error_message)
    return wrapper
