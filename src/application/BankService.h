#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <vector>
#include "../infrastructure/IBankRepository.h"

class BankService {
public:
    BankService(IBankRepository& repository) : repository(repository) {}

    void AddCustomer(const Customer& customer) {
        repository.AddCustomer(customer);
    }

    std::optional<Customer> GetCustomer(const int& accNum) {
        return repository.GetCustomer(accNum);
    }

    std::vector<Customer> GetCustomers() {
        return repository.GetCustomers();
    }

    void RemoveCustomer(const Customer& customer) {
        repository.RemoveCustomer(customer);
    }

    bool ValidateCustomer(const Customer& customer) {
        return repository.ValidateCustomer(customer);
    }

    bool TransferMoney(const int& senderAccNum, const int& receiverAccNum, const int& amount) {
        return repository.TransferMoney(senderAccNum, receiverAccNum, amount);
    }

    void Deposit(const Customer& customer, const int& amount) {
        repository.Deposit(customer, amount);
    }

    void Withdraw(const Customer& customer, const int& amount) {
        repository.Withdraw(customer, amount);
    }

private:
    IBankRepository& repository;
};

#endif
