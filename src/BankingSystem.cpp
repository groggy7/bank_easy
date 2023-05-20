#include "BankingSystem.h"

void Bank::TransferMoney(Customer& sender, Customer& receiver, double amount)
{
	if (sender.GetBalance() < amount)
	{
		std::cout << "Insufficient funds!" << std::endl;
		return;
	}
	sender.SetBalance(amount, 0);
	receiver.SetBalance(amount, 1);
}

void Bank::AddCustomer(Customer& customer)
{
	customers.push_back(customer);
}

std::vector<Customer>& Bank::GetCustomers()
{
	return customers;
}

void Bank::RemoveCustomer(Customer& customer)
{

}

bool Bank::ValidateCustomer(Customer& customer)
{
	for (Customer c : customers)
	{
		if (c.GetPhoneNumber() == customer.GetPhoneNumber() && c.GetPassword() == customer.GetPassword()) {
			return true;
		}
	}
	return false;
}
