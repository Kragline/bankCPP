#pragma once

#include <vector>
#include <algorithm>
#include "Account.hpp"

class Bank
{
private:
	int						_nextAccountId;
	std::vector<Account>	_accounts;
public:
	Bank();
	Bank(const Bank &other) = delete;

	Bank	&operator=(const Bank &other) = delete;

	void	createAccount(const std::string& owner);
	Account	*findAccount(int accountId);

	void	deposit(int accountId, double amount);
	void	withdraw(int accountId, double amount);

	void	showAccount(int accountId);
	void	listAccounts() const ;

	void	printUsage() const ;

	// TODO
	void	saveToFile(const std::string& filename) const ;
	void	loadFromFile(const std::string& filename);

	~Bank();
private:
	std::string	_trimString(std::string str) const ;

};
