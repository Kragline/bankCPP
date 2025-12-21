#pragma once

#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Account
{
private:
	int			_accountId;
	double		_balance;
	std::string	_ownerName;
public:
	Account() = delete;
	Account(int Id, const std::string &owner);
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
