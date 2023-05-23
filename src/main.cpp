#include <iostream>
#include <mongocxx/database.hpp>
#include "domain/customer.h"
#include "application/BankService.h"
#include "infrastructure/MongoBankRepository.h"
template <typename T>
void Print(const T& t) {
	std::cout << t << std::endl;
}

template <typename T>
int Scan() {
	T t;
	std::cin >> t;
	return t;
}

int main()
{
	Customer user("John Doe", 123456789);
	user.SetBalance(1000);
	Customer user2("Lincoln Burrows", 536748982);
	user2.SetBalance(1000);

	MongoBankRepository mongo_bank_repository;
	
	BankService bankService(mongo_bank_repository);

	std::vector<Customer> customers = bankService.GetCustomers();
	for (auto& customer : customers) {
		std::cout << customer.GetAccountNumber() << std::endl;
	}
}