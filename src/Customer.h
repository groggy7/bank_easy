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
	Customer(const int& phoneNumber, const int& password)
		:
		phoneNumber(phoneNumber),
		password(password)
	{}

	const double& GetBalance() const;

	void SetBalance(const double& balance, bool mode);
	
	const int& GetAccountNumber() const;

	const int& GetPassword() const;

	const int& GetPhoneNumber() const;

	const std::string& GetLongName() const;

	friend std::ostream& operator<< (std::ostream& out, const Customer& Customer) {
			return out << "Name: " << Customer.longName <<
			"\nPhone Number: " << Customer.phoneNumber << 
			"\nAccount Number: " << Customer.accountNumber <<
			"\nBalance: " << Customer.balance << std::endl;
	}

private:
	std::string longName;
	int phoneNumber;
	int accountNumber;
	double balance;
	int password;
};
