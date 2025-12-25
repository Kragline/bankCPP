#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Account.hpp"

#define TABLE_CHARS 50
#define TABLE_WIDTH (TABLE_CHARS + 4)

class Bank
{
private:
	int						_nextAccountId;
	std::vector<Account>	_accounts;
public:
	Bank();
	Bank(const Bank &other) = delete;

	Bank	&operator=(const Bank &other) = delete;

	void	createAccount(const std::string &owner);
	void	deleteAccount(int accountId);

	Account	*findAccount(int accountId);

	void	deposit(int accountId, double amount);
	void	withdraw(int accountId, double amount);

	void	showAccount(int accountId);
	void	listAccounts() const ;

	void	printUsage() const ;

	void	saveToFile(const std::string &filename);
	void	overrideFromFile(const std::string &filename);

	~Bank();
private:
	void	_parseCsvLine(const std::string &line, int &ownerId, std::string &owner, double &balance);
	void	_createAccount(int ownerId, const std::string &owner, double balance);
};
