#include "Bank.hpp"
#include "input.hpp"

Bank::Bank() : _nextAccountId(0)
{
	std::cout << std::endl << YELLOW "\tWelcome to the bankshell" WHITE << std::endl << std::endl;

	std::ifstream	csvFile("data.csv");

	if (csvFile.peek() != std::fstream::traits_type::eof()) // if file is empty dont load anything
	{
		csvFile.close();
		overrideFromFile("data.csv");
	}
	csvFile.close();
}

void	Bank::createAccount(const std::string& owner)
{
	_accounts.emplace_back(_nextAccountId, owner);
	_nextAccountId++;
}

void	Bank::_createAccount(int ownerId, const std::string &owner, double balance)
{
	if (ownerId < 0)
		throw std::runtime_error("ID cant be negative");
		
	if (findAccount(ownerId))
		throw std::runtime_error("Duplicate account ID in file");
	
	if (balance < 0)
		throw std::runtime_error("Balance cant be negative");
	
	_accounts.emplace_back(ownerId, owner, balance);
	if (ownerId >= _nextAccountId)
		_nextAccountId = ownerId + 1;
}


Account	*Bank::findAccount(int accountId)
{
	std::vector<Account>::iterator	it = std::find_if(_accounts.begin(), _accounts.end(),
	[accountId](const Account &acc)
	{
		return (accountId == acc.getId());
	});
	if (it == _accounts.end())
		return (nullptr);
	return (&(*it));
}

void	Bank::deposit(int accountId, double amount)
{
	Account	*acc = findAccount(accountId);
	if (acc == nullptr)
	{
		std::cerr << RED "Account with the ID of " << accountId << " doesn't exist!" WHITE << std::endl;
		return ;
	}
	acc->deposit(amount);
	std::cout << "Deposit for [" << accountId << "] " << acc->getOwner() << " was successfully completed!" << std::endl;
}

void	Bank::withdraw(int accountId, double amount)
{
	Account	*acc = findAccount(accountId);
	if (acc == nullptr)
	{
		std::cerr << RED "Account with the ID of " << accountId << " doesn't exist!" WHITE << std::endl;
		return ;
	}
	try
	{
		acc->withdraw(amount);
		std::cout << "Withdraw for [" << accountId << "] " << acc->getOwner() << " was successfully completed!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED "Withdraw for [" << accountId << "] " << acc->getOwner() << " failed: " << e.what() << WHITE << std::endl;
	}
}

void	Bank::showAccount(int accountId)
{
	if (_accounts.empty())
	{
		std::cerr << RED "No accounts in the bank!" WHITE << std::endl;
		return ;
	}
	Account	*acc = findAccount(accountId);
	if (acc == nullptr)
	{
		std::cerr << RED "Account with the ID of " << accountId << " doesn't exist!" WHITE << std::endl;
		return ;
	}
	acc->printAllInfo();
}

void	Bank::listAccounts() const
{
	if (_accounts.empty())
	{
		std::cerr << RED "No accounts in the bank!" WHITE << std::endl;
		return ;
	}

	std::cout << std::right << WHITE_BOLD;
	for (int i = 0; i < TABLE_WIDTH; i++)
		std::cout << "-";
	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << "Account ID" << "|";
	std::cout << std::setw(20) << "Owner name" << "|";
	std::cout << std::setw(20) << "Balance" << "|" << std::endl ;
	for (int i = 0; i < TABLE_WIDTH; i++)
		std::cout << "-";
	std::cout << WHITE << std::endl;

	for (size_t i = 0; i < _accounts.size(); i++)
		_accounts[i].printFormatted();
	for (int i = 0; i < TABLE_WIDTH; i++)
		std::cout << "-";
	std::cout << std::endl;
}

void	Bank::printUsage() const
{
	std::cout << BLUE "Avilable commands" WHITE << std::endl;

	std::cout << BLUE "1)" GREEN " create" PURPLE " <owner name>" WHITE << std::endl;
	std::cout << BLUE "2)" GREEN " deposit" PURPLE " <id> <amount>" WHITE << std::endl;
	std::cout << BLUE "3)" GREEN " withdraw" PURPLE " <id> <amount>" WHITE << std::endl;
	std::cout << BLUE "4)" GREEN " show" PURPLE " <id>" WHITE << std::endl;
	std::cout << BLUE "5)" GREEN " list" WHITE << std::endl;
	std::cout << BLUE "6)" GREEN " save" PURPLE " <filename>" WHITE << std::endl;
	std::cout << BLUE "7)" GREEN " override" PURPLE " <filename>" WHITE << std::endl;
	std::cout << BLUE "8)" GREEN " exit" WHITE << std::endl << std::endl;
}

void	Bank::saveToFile(const std::string &filename)
{
	std::cout << GREEN "-- Saving data to " << filename << "... --" << WHITE << std::endl;

	std::ofstream	csvFile(filename);

	for (size_t i = 0; i < _accounts.size(); i++)
		csvFile << _accounts[i].getId() << ';' << _accounts[i].getOwner() << ';' << _accounts[i].getBalance() << '\n';
	
	std::cout << GREEN "-- Data save finished successfully! --" WHITE << std::endl;
}

void	Bank::_parseCsvLine(const std::string &line, int &ownerId, std::string &owner, double &balance)
{
	try
	{
		std::string			ownerIdStr;
		std::string			balanceStr;
		std::stringstream	ss(line);

		getArgumentFromStream(ss, ownerIdStr, "Specify owner ID in the file", ';');
		convertNumber(ownerIdStr, ownerId);
		getArgumentFromStream(ss, owner, "Specify owner name in the file", ';');
		getArgumentFromStream(ss, balanceStr, "Specify balance in the file", '\n');
		convertNumber(balanceStr, balance);
	}
	catch(const std::exception& e)
	{
		throw ;
	}
}

void	Bank::overrideFromFile(const std::string &filename)
{
	std::cout << GREEN "-- Importing data from " << filename << "... --" << WHITE << std::endl;

	std::string		line;
	std::ifstream	csvFile(filename);

	if (!csvFile.is_open())
		throw std::runtime_error("Failed to open " + filename + "\n-- Data import stopped --");

	if (csvFile.peek() == std::fstream::traits_type::eof())
		throw std::runtime_error(filename + " is empty\n-- Data import stopped --");

	_accounts.clear();
	_nextAccountId = 0;
	while (std::getline(csvFile, line))
	{
		try
		{
			int							ownerId;
			double						balance;
			std::string					owner;
			
			_parseCsvLine(line, ownerId, owner, balance);
			_createAccount(ownerId, owner, balance);
		}
		catch(const std::exception& e)
		{
			std::cerr << RED << e.what() << WHITE << std::endl;
		}
	}
	csvFile.close();
	std::cout << GREEN "-- Data import finished! --" WHITE << std::endl;
}

Bank::~Bank()
{
	if (!_accounts.empty())
		saveToFile("data.csv");
	
	std::cout << std:: endl << YELLOW "\tbankshell was closed!" WHITE << std::endl << std::endl;
}
