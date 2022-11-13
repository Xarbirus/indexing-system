import sys
from input.processor import Processor
from utils.check_address import is_host_address_correct


def main() -> int:
    if len(sys.argv) != 2:
        print("You should specify the server 'host:port' as an argument.")
        return 1
    address = sys.argv[1].lower()
    if not is_host_address_correct(address):
        print("'host:port' is not correct. You can use 'ip:port' or 'localhost:port' as an argument.")
        return 1
    Processor(address).run()
    return 0


if __name__ == '__main__':
    sys.exit(main())
