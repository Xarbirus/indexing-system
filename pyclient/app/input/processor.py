from . import commands
from typing import Type


class Processor:
    """
    A class used to process user input (from input())

    Methods
    -------
    run()
        Starts reading and processing user input
    """

    def __init__(self, address: str):
        """
        Parameters
        ----------
        address : str
            address of the indexing-system server
        """
        self.__stop = False
        self.__processors = dict()
        self.__add("help", commands.HelpProcessor, self.__processors)
        self.__add("index", commands.IndexProcessor, address)
        self.__add("roots", commands.RootsProcessor, address)
        self.__add("get", commands.GetProcessor, address)
        self.__add("remove", commands.RemoveProcessor, address)
        self.__add("clear", commands.ClearProcessor, address)
        self.__add("quit", commands.QuitProcessor, self)

    def run(self) -> None:
        """
        Starts reading and processing user input
        """
        print("Client started.")
        while not self.__stop:
            command = input().split(" ", 1)
            processor = self.__processors.get(command[0].lower())
            if processor:
                processor.execute(command[1].strip() if len(command) == 2 else "")
            else:
                print(f"Unknown command '{command[0]}'.")
                self.__processors.get("help").execute()

    def stop(self) -> None:
        self.__stop = True

    def __add(self, command: str, processor: Type[commands.ProcessorBase], *args) -> None:
        """
        Adds command processor

        Parameters
        ----------
        command : str
            Name of a command to process
        processor : Type[commands.ProcessorBase]
            Type of processor
        *args : optional
            Additional arguments to create processor
        """
        self.__processors.update({command: processor(command, *args)})
