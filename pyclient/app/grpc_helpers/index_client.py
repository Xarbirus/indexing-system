import grpc
from typing import Union
from grpc_helpers.utils import safe_grpc_call as safe_call, GrpcError


class IndexClient:
    """
    A client for gRPC calls to index_service

    Attributes
    ----------
    address : str
        'host:port' address of the server
    options : tuple
        special options for gRPC calls

    Methods
    -------
    add_root(root)
        starts indexing of the given root
    get_roots()
        reads all available roots in the indexing-system
    get_files(word)
        reads a list of files containing a word
    get_files_in_root(word, root)
        reads a list of files containing a word in a root
    remove_root()
        removes a given root from the indexing-system
    clear_roots()
        removes all roots from the indexing-system
    """
    from generated.grpc import index_pb2_grpc as index_grpc
    from generated.grpc import index_pb2 as index_pb

    def __init__(self, address: str):
        self.address = address
        self.options = (('grpc.enable_http_proxy', 0),)

    @safe_call
    def add_root(self, root: str) -> Union[index_pb.add_root_result, GrpcError]:
        """
        Starts indexing of the given root on the server

        Parameters
        ----------
        root : str
            absolute path to directory to index
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.add_root(self.index_pb.root(value=root))

    @safe_call
    def get_roots(self) -> Union[index_pb.get_roots_result, GrpcError]:
        """
        Reads all available roots in the indexing-system
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.get_roots(self.index_pb.empty())

    @safe_call
    def get_files(self, word: str) -> Union[index_pb.get_files_result, GrpcError]:
        """
        Reads a list of files containing a word

        Parameters
        ----------
        word : str
            a word to find
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.get_files(self.index_pb.get_files_request(word=word))

    @safe_call
    def get_files_in_root(self, word: str, root: str) -> Union[index_pb.get_files_result, GrpcError]:
        """
        Reads a list of files containing a word in a root

        Parameters
        ----------
        word : str
            a word to find
        root : str
            a root to search
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.get_files_in_root(self.index_pb.get_files_in_root_request(word=word, root=root))

    @safe_call
    def remove_root(self, root: str) -> Union[index_pb.add_root_result, GrpcError]:
        """
        Removes a given root from the indexing-system

        Parameters
        ----------
        root : str
            absolute path to directory to remove
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.remove_root(self.index_pb.root(value=root))

    @safe_call
    def clear_roots(self) -> Union[index_pb.remove_root_result, GrpcError]:
        """
        Removes all roots from the indexing-system
        """
        with grpc.insecure_channel(self.address, self.options) as channel:
            stub = self.index_grpc.index_serviceStub(channel)
            return stub.clear_roots(self.index_pb.empty())
