#pragma once

#include "Bank.hpp"

#define STOP_LOOP 0
#define CONTINUE_LOOP 1

int		processInput(const std::string &input, Bank &bank);
void	getArgumentFromStream(std::stringstream &stream, std::string &argument, const char *errorMsg, char delimiter);

template <typename T>
void	convertNumber(const std::string &sValue, T &value)
{
	std::stringstream	valueStream(sValue);
	valueStream >> value;

	if (valueStream.fail())
		throw std::runtime_error("Invalid numeric value");
}
