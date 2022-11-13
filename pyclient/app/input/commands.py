class ProcessorBase:
    """
    A base class for all command processors

    Attributes
    ----------
    command : str
        the name of the command
    description : str
        the full description of the command

    Methods
    -------
    execute(arguments) -> bool
        Starts processing of given arguments
    """
    def __init__(self, command: str, description: str):
        """
        Parameters
        ----------
        command : str
            the name of the command to process
        description : str
            the full description of the command
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
    A class to stop the client

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
            the name of the quit command
        client
            the command processor that should be stopped
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
        print("Client stopped.")
        self.client.stop()


class HelpProcessor(ProcessorBase):
    """
    A class to print help message

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
            the name of the help command
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
            the name of the command to print help (default is "")
        """
        if command and command in self.processors:
            print(f"{self.processors[command]}")
        else:
            print("Available commands:")
            for processor in self.processors.values():
                print(f"\t{processor}")


class IndexProcessor(ProcessorBase):
    def __init__(self, command: str, address: str):
        super().__init__(command, f"Use '{command} <absolute_path_to_directory>' "
                                  f"to start indexing the directory.")
        self.address = address

    def execute(self, arguments: str):
        pass


class RootsProcessor(ProcessorBase):
    def __init__(self, command: str, address: str):
        super().__init__(command, f"Use '{command}' to get all indexed roots.")
        self.address = address

    def execute(self, arguments: str):
        pass


class GetProcessor(ProcessorBase):
    def __init__(self, command: str, address: str):
        super().__init__(command, f"Use '{command} <word>' to see all files with the <word>. "
                                  f"Use '{command} <word> <absolute_path_to_directory>' "
                                  f"to see all files with the <word> in the <absolute_path_to_directory>.")
        self.address = address

    def execute(self, arguments: str):
        pass


class RemoveProcessor(ProcessorBase):
    def __init__(self, command: str, address: str):
        super().__init__(command, f"Use '{command} <absolute_path_to_directory>' "
                                  f"to remove the directory from the index.")
        self.address = address

    def execute(self, arguments: str):
        pass


class ClearProcessor(ProcessorBase):
    def __init__(self, command: str, address: str):
        super().__init__(command, f"Use '{command}' to remove everything from the index.")
        self.address = address

    def execute(self, arguments: str):
        pass
