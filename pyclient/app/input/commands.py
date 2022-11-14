from grpc_helpers.index_client import IndexClient, GrpcError


class ProcessorBase:
    """
    A base class for all command processors

    Attributes
    ----------
    command : str
        a name of a command
    description : str
        a full description of a command

    Methods
    -------
    execute(arguments)
        Processing of given arguments
    """
    def __init__(self, command: str, description: str):
        """
        Parameters
        ----------
        command : str
            a name of a command to process
        description : str
            a full description of a command
        """
        self.command = command
        self.description = description

    def __str__(self):
        return f"{self.command:<8}{self.description}"

    def execute(self, arguments: str) -> None:
        """
        Runs command processing with given arguments

        Parameters
        ----------
        arguments : str
            joined string of arguments to process
        """
        pass


class QuitProcessor(ProcessorBase):
    """
    A class for stopping a client

    Methods
    -------
    execute(arguments="")
        Stops the given client
    """
    def __init__(self, command: str, client):
        """
        Parameters
        ----------
        command : str
            a name of the quit command
        client
            a client that should be stopped
        """
        super().__init__(command, f"Use '{command}' to stop the client.")
        self.client = client

    def execute(self, arguments: str = "") -> None:
        """
        Stops the client

        Parameters
        ----------
        arguments : str, optional
            dummy argument (default is "")
        """
        if arguments.strip():
            print(self.description)
            return
        print("Client stopped.")
        self.client.stop()


class HelpProcessor(ProcessorBase):
    """
    A class for printing help message

    Methods
    -------
    execute(command="")
        Prints help message for a specific command or a list of commands
    """
    def __init__(self, command: str, processors: dict):
        """
        Parameters
        ----------
        command : str
            a name of the help command
        processors : dict
            the dictionary with all client's processors
        """
        super().__init__(command, f"Use '{command}' to see a list of commands. "
                                  f"Use '{command} <command>' to see information about a specific command.")
        self.processors = processors

    def execute(self, command: str = "") -> None:
        """
        Prints help message for a specific command or a list of commands

        Parameters
        ----------
        command : str, optional
            a name of a command to print help (default is "")
        """
        if command and command in self.processors:
            print(f"{self.processors[command]}")
        else:
            print("Available commands:")
            for processor in self.processors.values():
                print(f"\t{processor}")


class IndexProcessor(ProcessorBase):
    """
    A class for indexing a given root on the server

    Attributes
    ----------
    grpc_client : IndexClient
        a grpc client to the server

    Methods
    -------
    execute(root)
        starts indexing of the given root
    """
    def __init__(self, command: str, address: str):
        """
        Parameters
        ----------
        command : str
            a name of the index command
        address : str
            'host:port' address of the server
        """
        super().__init__(command, f"Use '{command} <absolute_path_to_directory>' to start indexing the directory.")
        self.grpc_client = IndexClient(address)

    def execute(self, root: str) -> None:
        """
        Starts indexing of the given root on the server

        Parameters
        ----------
        root : str
            absolute path to directory to index
        """
        root = root.strip()
        if not root:
            print(self.description)
            return
        response = self.grpc_client.add_root(root)
        if isinstance(response, GrpcError):
            print(response)
        else:
            print(f"Finished in {response.duration.seconds // 60} minute(s). {response.files} file(s) indexed.")


class RootsProcessor(ProcessorBase):
    """
    A class for getting all available roots in the indexing-system

    Attributes
    ----------
    grpc_client : IndexClient
        a grpc client to the server

    Methods
    -------
    execute(arguments="")
        prints all available roots in the indexing-system
    """
    def __init__(self, command: str, address: str):
        """
        Parameters
        ----------
        command : str
            a name of the roots command
        address : str
            'host:port' address of the server
        """
        super().__init__(command, f"Use '{command}' to get all indexed roots.")
        self.grpc_client = IndexClient(address)

    def execute(self, arguments: str = "") -> None:
        """
        Prints all available roots in the indexing-system

        Parameters
        ----------
        arguments : str, optional
            dummy argument (default is "")
        """
        if arguments.strip():
            print(self.description)
            return
        response = self.grpc_client.get_roots()
        if isinstance(response, GrpcError):
            print(response)
        else:
            print(f"Finished in {response.duration.seconds // 60} minute(s).", end=' ')
            if response.roots:
                print("Available roots:")
                [print('\t', root) for root in response.roots]
            else:
                print("There are no available roots.")


class GetProcessor(ProcessorBase):
    """
    A class for getting a list of files with some specific word

    Attributes
    ----------
    grpc_client : IndexClient
        a grpc client to the server

    Methods
    -------
    execute(arguments)
        prints a list of files with the word
    """
    def __init__(self, command: str, address: str):
        """
        Parameters
        ----------
        command : str
            a name of the get command
        address : str
            'host:port' address of the server
        """
        super().__init__(command, f"Use '{command} <word>' to see all files with the <word>. "
                                  f"Use '{command} <word> <absolute_path_to_directory>' "
                                  f"to see all files with the <word> in the <absolute_path_to_directory>.")
        self.grpc_client = IndexClient(address)

    def execute(self, arguments: str) -> None:
        """
        If 'arguments' contains only a word, prints a list of files containing it;
        if 'arguments' contains a word and a root, separated by a whitespace,
        prints a list of files from a root containing the specified word

        Parameters
        ----------
        arguments : str
            a 'word' or a word and a root, separated by a whitespace, like 'word root'
        """
        arguments = arguments.strip()
        if not arguments:
            print(self.description)
            return
        arguments = arguments.split(" ", 1)
        if len(arguments) == 1:
            response = self.grpc_client.get_files(arguments[0])
        else:
            response = self.grpc_client.get_files_in_root(arguments[0], arguments[1])
        if isinstance(response, GrpcError):
            print(response)
        else:
            total_words = sum([sum(file.word_counter for file in root.files) for root in response.roots])
            total_files = sum([len(root.files) for root in response.roots])
            print(f"Finished in {response.duration.seconds // 60} minute(s). "
                  f"{total_words} usage(s) found{f' in {total_files} file(s):' if total_words != 0 else '.'}")
            for root in response.roots:
                if root.files:
                    print(f"In root: {root.root_path}")
                    [print('\t', file.filename) for file in root.files]


class RemoveProcessor(ProcessorBase):
    """
    A class for removing a given root from the indexing-system

    Attributes
    ----------
    grpc_client : IndexClient
        a grpc client to the server

    Methods
    -------
    execute(arguments)
        removes a given root from the indexing-system
    """
    def __init__(self, command: str, address: str):
        """
        Parameters
        ----------
        command : str
            a name of the get command
        address : str
            'host:port' address of the server
        """
        super().__init__(command, f"Use '{command} <absolute_path_to_directory>' "
                                  f"to remove the directory from the index.")
        self.grpc_client = IndexClient(address)

    def execute(self, root: str):
        """
        Removes a given root from the indexing-system

        Parameters
        ----------
        root : str
            absolute path to directory to remove
        """
        root = root.strip()
        if not root:
            print(self.description)
            return
        response = self.grpc_client.remove_root(root)
        if isinstance(response, GrpcError):
            print(response)
        else:
            print(f"Finished in {response.duration.seconds // 60} minute(s).")


class ClearProcessor(ProcessorBase):
    """
    A class for removing all roots from the indexing-system

    Attributes
    ----------
    grpc_client : IndexClient
        a grpc client to the server

    Methods
    -------
    execute(arguments)
        removes all roots from the indexing-system
    """
    def __init__(self, command: str, address: str):
        """
        Parameters
        ----------
        command : str
            a name of the get command
        address : str
            'host:port' address of the server
        """
        super().__init__(command, f"Use '{command}' to remove everything from the index.")
        self.grpc_client = IndexClient(address)

    def execute(self, arguments: str = ""):
        """
        Removes all roots from the indexing-system

        Parameters
        ----------
        arguments : str, optional
            dummy argument (default is "")
        """
        if arguments.strip():
            print(self.description)
            return
        response = self.grpc_client.clear_roots()
        if isinstance(response, GrpcError):
            print(response)
        else:
            print(f"Finished in {response.duration.seconds // 60} minute(s).")
