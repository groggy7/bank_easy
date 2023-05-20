#include <iostream>
#include "Customer.h"
#include "BankingSystem.h"

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
	Bank bank; 
	
	Customer user("John Doe", 123456789);
	user.SetBalance(1000, 1);
	Customer user2("Lincoln Burrows", 536748982);
	user2.SetBalance(1000, 1);

	bank.AddCustomer(user);
	bank.AddCustomer(user2);
	
	while (true) {
		Print("Welcome to BankEasy!");

		Print("Enter your account number: ");
		int accountNumber = Scan<int>();
		
		Print("Enter your password: ");
		int password = Scan<int>();

		Customer customer(accountNumber, password);
		
		if (!bank.ValidateCustomer(customer)) {
			Print("Invalid account number or password!");
			continue;
		}

		Print("Welcome " + customer.GetLongName() + "!");

	}
}