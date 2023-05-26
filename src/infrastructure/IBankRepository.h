#ifndef IBANKREPOSITORY_H
#define IBANKREPOSITORY_H

#include <vector>
#include <optional>
#include "../domain/customer.h"

class IBankRepository {
public:
    virtual void AddCustomer(const Customer& customer) = 0;
    virtual std::optional<Customer> GetCustomer(const int&) = 0;
    virtual std::vector<Customer> GetCustomers() = 0;
    virtual void RemoveCustomer(const Customer& customer) = 0;
    virtual bool ValidateCustomer(const Customer& customer) = 0;
    virtual bool TransferMoney(const int& senderAccNum, const int& receiverAccNum, const int& amount) = 0;
    virtual void Deposit(const Customer& customer, const int& amount) = 0;
    virtual void Withdraw(const Customer& customer, const int& amount) = 0;
    virtual ~IBankRepository() {}
};

#endif
