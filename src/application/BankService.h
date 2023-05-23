#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <vector>
#include "../infrastructure/IBankRepository.h"

class BankService {
public:
    BankService(IBankRepository& repository) : repository(repository) {}

    void AddCustomer(const std::string& name, double balance) {
        Customer customer(name, balance);
        repository.AddCustomer(customer);
    }

    std::vector<Customer> GetCustomers() {
        return repository.GetCustomers();
    }

    void RemoveCustomer(const std::string& name) {
        Customer customer(name, 0.0);
        repository.RemoveCustomer(customer);
    }

    bool ValidateCustomer(const std::string& name) {
        Customer customer(name, 0.0);
        return repository.ValidateCustomer(customer);
    }

    void TransferMoney(const std::string& senderName, const std::string& receiverName, double amount) {
        Customer sender(senderName, 0.0);
        Customer receiver(receiverName, 0.0);
        repository.TransferMoney(sender, receiver, amount);
    }

private:
    IBankRepository& repository;
};

#endif
