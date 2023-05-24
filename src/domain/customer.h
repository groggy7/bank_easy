#pragma once
#include <string>
#include <iostream>
#include <random>

class Customer
{
public:
	Customer(const std::string& longName, const int& phoneNumber, const int& password) 
		:
		longName(longName),
		phoneNumber(phoneNumber),
		password(password)
	{
		balance = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(111'111'111, 999'999'999);
		accountNumber = dis(gen);
	}

	Customer(const int& accountNumber, const int& password) 
		: 
		accountNumber(accountNumber),
		password(password) 
	{}

	Customer() {}

	const std::string& GetLongName() const
	{
		return longName;
	}

	void SetLongName(const std::string& name) {
		longName = name;
	}

	const int& GetAccountNumber() const
	{
		return accountNumber;
	}

	void SetAccountNumber(const int& accNum) {
		accountNumber = accNum;
	}

	const int& GetPassword() const
	{
		return password;
	}

	void SetPassword(const int &pass)
	{
		password = pass;
	}

	const int& GetPhoneNumber() const
	{
		return phoneNumber;
	}

	void SetPhoneNumber(const int &phoneNum)
	{
		phoneNumber = phoneNum;
	}

	const int& GetBalance() const
	{
		return balance;
	}

	void SetBalance(const double &b)
	{
		balance = b;
	}

private:
	std::string longName;
	int phoneNumber;
	int accountNumber;
	int balance;
	int password;
};
