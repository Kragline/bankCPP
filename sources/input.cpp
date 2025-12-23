#include "input.hpp"

std::string	trimString(std::string str)
{
	size_t	start = str.find_first_not_of(" \t");
	size_t	end = str.find_last_not_of(" \t");

	if (start == std::string::npos)
		str = "";
	else
		str = str.substr(start, end - start + 1);
	return (str);
}

void	getArgumentFromStream(std::stringstream &stream, std::string &argument, const char *errorMsg, char delimiter)
{
	std::getline(stream, argument, delimiter);
	argument = trimString(argument);
	if (argument.empty())
		throw std::runtime_error(errorMsg);
}

void	processCreate(std::stringstream &ss, Bank &bank)
{
	std::string	ownerName;
	
	try
	{
		getArgumentFromStream(ss, ownerName, "Specify owner name for the account!", '\n');
		bank.createAccount(ownerName);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

void	processFile(std::stringstream &ss, Bank &bank, void (Bank::*method)(int, double))
{
	int			accountId;
	double		amount;
	std::string	accountIdStr;
	std::string	amountStr;

	try
	{
		getArgumentFromStream(ss, accountIdStr, "Specify account id!", ' ');
		convertNumber(accountIdStr, accountId);
		getArgumentFromStream(ss, amountStr, "Specify an amount id!", '\n');
		convertNumber(amountStr, amount);
		(bank.*method)(accountId, amount);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

void	processFile(std::stringstream &ss, Bank &bank, void (Bank::*method)(const std::string &))
{
	std::string	filename;

	try
	{
		getArgumentFromStream(ss, filename, "Specify filename!", '\n');
		(bank.*method)(filename);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

void	processShow(std::stringstream &ss, Bank &bank)
{
	int			ownerName;
	std::string	ownerNameStr;
	
	try
	{
		getArgumentFromStream(ss, ownerNameStr, "Specify account id!", '\n');
		convertNumber(ownerNameStr, ownerName);
		bank.showAccount(ownerName);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

int	processInput(const std::string &input, Bank &bank)
{
	if (input.empty())
		return (CONTINUE_LOOP);
	
	std::string			command;
	std::stringstream	ss(input);

	if (input.find_first_not_of(" \t") == std::string::npos)
		return (CONTINUE_LOOP);

	std::getline(ss, command, ' ');
	command = trimString(command);

	if (command == "create")
		processCreate(ss, bank);
	else if (command == "deposit")
		processFile(ss, bank, &Bank::deposit);
	else if (command == "withdraw")
		processFile(ss, bank, &Bank::withdraw);
	else if (command == "show")
		processShow(ss, bank);
	else if (command == "list")
		bank.listAccounts();
	else if (command == "save")
		processFile(ss, bank, &Bank::saveToFile);
	else if (command == "load")
		processFile(ss, bank, &Bank::loadFromFile);
	else if (command == "exit")
		return (STOP_LOOP);
	else
		std::cerr << RED << "Invalid command!" WHITE << std::endl;
	return (CONTINUE_LOOP);
}
