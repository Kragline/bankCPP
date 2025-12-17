#include "input.hpp"

int	main()
{
	Bank	bank;
	std::string	userInput;

	std::cout << "Welcome to the bank" << std::endl << std::endl;
	bank.printUsage();
	while (true)
	{
		std::cout << "Enter command -> ";
		getline(std::cin, userInput);
		if (!processInput(userInput, bank))
			break ;
		if (std::cin.eof())
		{
			std::cout << std::endl;
			break ;
		}
	}
	std::cout << std:: endl << "Bank was closed!" << std::endl;
	return (0);
}
