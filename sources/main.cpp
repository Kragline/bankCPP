#include "input.hpp"

int	main()
{
	Bank		bank;
	std::string	userInput;

	std::cout << std::endl << YELLOW "\tWelcome to the bankshell" WHITE << std::endl << std::endl;
	bank.printUsage();
	while (true)
	{
		std::cout << GREEN_BOLD "💸 bankshell 💸" WHITE_BOLD " → " WHITE;
		getline(std::cin, userInput);
		if (!processInput(userInput, bank))
			break ;
		if (std::cin.eof())
		{
			std::cout << std::endl;
			break ;
		}
	}
	std::cout << std:: endl << YELLOW "\tbankshell was closed!" WHITE << std::endl << std::endl;
	return (0);
}
