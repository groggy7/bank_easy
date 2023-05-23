#pragma once
#include <string>
#include <iostream>
#include <random>

class Customer
{
public:
	Customer(const std::string& longName, const int& phoneNumber) 
		:
		longName(longName),
		phoneNumber(phoneNumber)
	{
		balance = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(111'111'111, 999'999'999);
		accountNumber = dis(gen);
		password = 1234;
	}
	Customer(const std::string& longName, const int& accountNumber, const int& phoneNumber, const int& password, const double& balance)
		:
		longName(longName),
		accountNumber(accountNumber),
		phoneNumber(phoneNumber),
		password(password),
		balance(balance)
	{}

	Customer() {}
	const std::string& GetLongName() const;
	
	void SetLongName(const std::string& name) {
		longName = name;
	}

	const int& GetAccountNumber() const;

	void SetAccountNumber(const long long& accNum) {
		accountNumber = accNum;
	}

	const int& GetPassword() const;

	void SetPassword(const int8_t& pass) {
		password = pass;
	}

	const int& GetPhoneNumber() const;

	void SetPhoneNumber(const long long& phoneNum) {
		phoneNumber = phoneNumber;
	}

	const double& GetBalance() const;

	void SetBalance(const double& balance);
private:
	std::string longName;
	int phoneNumber;
	int accountNumber;
	double balance;
	int8_t password;
};
