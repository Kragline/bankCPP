#pragma once

#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>

#define RED "\033[1;31m"
#define WHITE "\033[0m"
#define WHITE_BOLD "\033[1;37m"
#define GREEN "\033[0;32m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"

class Account
{
private:
	int			_accountId;
	double		_balance;
	std::string	_ownerName;
public:
	Account() = delete;
	Account(int Id, const std::string &owner);
	Account(int Id, const std::string &owner, double balance); // used in csv parsing only
	Account(const Account &other);

	Account	&operator=(const Account &other);

	int			getId() const ;
	double		getBalance() const ;
	std::string	getOwner() const ;

	void		deposit(double amount);
	void		withdraw(double amount);

	void		printFormatted() const ;
	void		printAllInfo() const ;

	~Account();
private:
	std::string	_formatString(const std::string &str) const ;
};
