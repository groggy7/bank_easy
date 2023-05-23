#ifndef IBANKREPOSITORY_H
#define IBANKREPOSITORY_H

#include <vector>
#include "../domain/customer.h"

class IBankRepository {
public:
    virtual void AddCustomer(Customer& customer) = 0;
    virtual std::vector<Customer> GetCustomers() = 0;
    virtual void RemoveCustomer(Customer& customer) = 0;
    virtual bool ValidateCustomer(Customer& customer) = 0;
    virtual void TransferMoney(Customer& sender, Customer& receiver, double amount) = 0;

    virtual ~IBankRepository() {}
};

#endif
