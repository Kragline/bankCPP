#include "Bank.hpp"

Bank::Bank() : _nextAccountId(0) {}

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
		std::cerr << "Account with the ID of " << accountId << " doesn't exist!" << std::endl;
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
		std::cerr << "Account with the ID of " << accountId << " doesn't exist!" << std::endl;
		return ;
	}
	try
	{
		acc->withdraw(amount);
		std::cout << "Withdraw for [" << accountId << "] " << acc->getOwner() << " was successfully completed!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Withdraw for [" << accountId << "] " << acc->getOwner() << " failed: " << e.what() << std::endl;
	}
}

void	Bank::showAccount(int accountId)
{
	if (_accounts.empty())
	{
		std::cerr << "No accounts in the bank!" << std::endl;
		return ;
	}
	Account	*acc = findAccount(accountId);
	if (acc == nullptr)
	{
		std::cerr << "Account with the ID of " << accountId << " doesn't exist!" << std::endl;
		return ;
	}
	acc->printAllInfo();
}

void	Bank::listAccounts() const
{
	if (_accounts.empty())
	{
		std::cerr << "No accounts in the bank!" << std::endl;
		return ;
	}

	std::cout << std::right;
	std::cout << "|" << std::setw(10) << "Account ID" << "|";
	std::cout << std::setw(20) << "Owner name" << "|";
	std::cout << std::setw(20) << "Balance" << "|" << std::endl ;
	for (size_t i = 0; i < _accounts.size(); i++)
		_accounts[i].printFormatted();
}

void	Bank::printUsage() const
{
	std::cout << "All avilable commands" << std::endl << std::endl;

	std::cout << "create <owner name>" << std::endl;
	std::cout << "deposit <id> <amount>" << std::endl;
	std::cout << "withdraw <id> <amount>" << std::endl;
	std::cout << "show <id>" << std::endl;
	std::cout << "list" << std::endl;

	std::cout << "exit" << std::endl << std::endl;
}

Bank::~Bank() {}
