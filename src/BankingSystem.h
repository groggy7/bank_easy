#pragma once
#include <vector>
#include "Customer.h"
#include <cassert>

class Bank
{
public:
	void AddCustomer(Customer& customer);
	std::vector<Customer>& GetCustomers();
	void RemoveCustomer(Customer& customer);
	bool ValidateCustomer(Customer& customer);
	void TransferMoney(Customer& sender, Customer& receiver, double amount);

private:
	std::vector<Customer> customers;
};
