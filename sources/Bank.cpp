#include "Bank.hpp"
#include "input.hpp"

Bank::Bank() : _nextAccountId(0)
{
	std::ifstream	csvFile("data.csv");

	if (csvFile.peek() != std::fstream::traits_type::eof())
	{
		csvFile.close();
		loadFromFile("data.csv");
	}
	csvFile.close();
}

void	Bank::createAccount(const std::string& owner)
{
	_accounts.emplace_back(Account(_nextAccountId, owner));
	_nextAccountId++;
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
	std::cout << BLUE "7)" GREEN " load" PURPLE " <filename>" WHITE << std::endl;
	std::cout << BLUE "8)" GREEN " exit" WHITE << std::endl << std::endl;
}

void	Bank::saveToFile(const std::string &filename)
{
	std::ofstream	csvFile(filename);

	for (size_t i = 0; i < _accounts.size(); i++)
		csvFile << _accounts[i].getId() << ';' << _accounts[i].getOwner() << ';' << _accounts[i].getBalance() << '\n';
}

void	Bank::loadFromFile(const std::string &filename)
{
	std::ifstream	csvFile(filename);

	if (!csvFile.is_open())
		throw std::runtime_error("Failed to open " + filename);

	if (csvFile.peek() == std::fstream::traits_type::eof())
		throw std::runtime_error(filename + " is empty");

	std::string	line;
	while (std::getline(csvFile, line))
	{
		try
		{
			int							ownerID;
			double						balance;
			std::array<std::string, 3>	readData;
			std::stringstream			ss(line);

			getArgumentFromStream(ss, readData[0], "Specify owner ID in the file", ';');
			convertNumber(readData[0], ownerID);
			getArgumentFromStream(ss, readData[1], "Specify owner name in the file", ';');
			getArgumentFromStream(ss, readData[2], "Specify balance in the file", '\n');
			convertNumber(readData[2], balance);

			Account	*acc = findAccount(ownerID);
			if (!acc)
			{
				createAccount(readData[1]);
				acc = findAccount(ownerID);
				acc->deposit(balance);

				continue;
			}
			double	currentBalance = acc->getBalance();
			if (balance > currentBalance)
				acc->deposit(balance - currentBalance);
			else
				acc->deposit(currentBalance - balance);
		}
		catch(const std::exception& e)
		{
			csvFile.close();
			std::cerr << e.what() << std::endl;
		}
	}
}

Bank::~Bank()
{
	if (!_accounts.empty())
		saveToFile("data.csv");
}
