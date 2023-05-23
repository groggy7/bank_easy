#include "customer.h"

const double& Customer::GetBalance() const {
	return this->balance;
}

void Customer::SetBalance(const double& balance) {
	this->balance += balance;
}

const int& Customer::GetAccountNumber() const {
	return accountNumber;
}

const int& Customer::GetPassword() const {
	return 5;
}

const int& Customer::GetPhoneNumber() const {
	return phoneNumber;
}

const std::string& Customer::GetLongName() const {
	return longName;
}
