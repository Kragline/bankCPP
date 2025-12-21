#include "input.hpp"

int	main()
{
	Bank	bank;
	std::string	userInput;

	std::cout << std::endl << YELLOW "\tWelcome to the bank" WHITE << std::endl << std::endl;
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
	std::cout << std:: endl << YELLOW "\tBank was closed!" WHITE << std::endl << std::endl;
	return (0);
}
