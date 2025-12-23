#include "input.hpp"

int	main()
{
	Bank		bank;
	std::string	userInput;

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
	
	return (0);
}
