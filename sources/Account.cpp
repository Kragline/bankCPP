#include "Account.hpp"

Account::Account(int Id, const std::string &owner) : _accountId(Id), _balance(0), _ownerName(owner)
{
	std::cout << "Account [" << _accountId << "] " << _ownerName << " was created!" << std::endl;
}

Account::Account(const Account &other) : _accountId(other._accountId), _balance(other._balance), _ownerName(other._ownerName) {}

Account	&Account::operator=(const Account &other)
{
	if (this != &other)
	{
		_accountId = other._accountId;
		_balance = other._balance;
		_ownerName = other._ownerName;
	}
	return (*this);
}

int			Account::getId() const { return (_accountId); }
double		Account::getBalance() const { return (_balance); }
std::string	Account::getOwner() const { return (_ownerName); }

void	Account::deposit(double amount) { _balance += amount; }

void	Account::withdraw(double amount)
{
	int	diff = _balance - amount;
	
	if (diff < 0)
		throw std::runtime_error("Insufficient funds");
	_balance = diff;
}

std::string	Account::_formatString(const std::string &str) const
{
	if (str.length() > 20)
		return (str.substr(0, 9) + ".");
	return (str);
}

void	Account::printFormatted() const
{
	std::stringstream	ss;
	ss << _balance;

	std::cout << "|" << std::setw(10) << _accountId << "|";
	std::cout << std::setw(20) << _formatString(_ownerName) << "|";
	std::cout << std::setw(20) << _formatString(ss.str()) << "|" << std::endl ;
}

void	Account::printAllInfo() const
{
	std::cout << "ID:		" << getId() << std::endl;
	std::cout << "Balance:	"  << getBalance() << std::endl;
	std::cout << "Owner name:	" << getOwner() << std::endl;
}

Account::~Account() {}
