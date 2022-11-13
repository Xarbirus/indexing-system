import re


def is_host_address_correct(address: str) -> bool:
    """
    The function checks: can the address be used to create grpc client?
    The address should look like ip:port or localhost:port

    Attributes
    ----------
    address : str
        the address to check

    Returns
    -------
    bool
        True if the address can be used otherwise False
    """
    pattern = "^(((([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}" \
              "([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))|localhost):" \
              "((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-9]{1,4}))$"

    return True if re.match(pattern, address) else False
