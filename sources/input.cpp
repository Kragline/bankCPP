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

void	createAction(std::stringstream &ss, Bank &bank)
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

void	listAction(const Bank &bank)
{
	try
	{
		bank.listAccounts();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

void	moneyActions(std::stringstream &ss, Bank &bank, void (Bank::*method)(int, double))
{
	int			accountId;
	double		amount;
	std::string	accountIdStr;
	std::string	amountStr;

	try
	{
		getArgumentFromStream(ss, accountIdStr, "Specify account id!", ' ');
		convertNumber(accountIdStr, accountId);
		getArgumentFromStream(ss, amountStr, "Specify amount of money!", '\n');
		convertNumber(amountStr, amount);
		(bank.*method)(accountId, amount);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << WHITE << std::endl;
	}
}

void	fileActions(std::stringstream &ss, Bank &bank, void (Bank::*method)(const std::string &))
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

void	accountActions(std::stringstream &ss, Bank &bank, void (Bank::*method)(int))
{
	int			ownerName;
	std::string	ownerNameStr;
	
	try
	{
		getArgumentFromStream(ss, ownerNameStr, "Specify account id!", '\n');
		convertNumber(ownerNameStr, ownerName);
		(bank.*method)(ownerName);
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
		createAction(ss, bank);
	else if (command == "delete")
		accountActions(ss, bank, &Bank::deleteAccount);
	else if (command == "deposit")
		moneyActions(ss, bank, &Bank::deposit);
	else if (command == "withdraw")
		moneyActions(ss, bank, &Bank::withdraw);
	else if (command == "show")
		accountActions(ss, bank, &Bank::showAccount);
	else if (command == "list")
		listAction(bank);
	else if (command == "save")
		fileActions(ss, bank, &Bank::saveToFile);
	else if (command == "override")
		fileActions(ss, bank, &Bank::overrideFromFile);
	else if (command == "exit")
		return (STOP_LOOP);
	else
		std::cerr << RED << "Invalid command!" WHITE << std::endl;
	return (CONTINUE_LOOP);
}
