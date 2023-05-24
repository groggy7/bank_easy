#include <iostream>
#include <mongocxx/database.hpp>
#include "domain/customer.h"
#include "application/BankService.h"
#include "infrastructure/MongoBankRepository.h"

using namespace std::literals;

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

int main() {
    MongoBankRepository mongo_bank_repository;
    BankService bankService(mongo_bank_repository);

    while (true) {
        Print("Welcome to Bank Easy!"s);
        Print("Please enter your account number: ");
        int64_t account_number = Scan<int64_t>();
		if (account_number < 0 || account_number > 2147483647) {
			Print("Invalid account number."s);
			continue;
		}

        Print("Please enter your password: ");
		int64_t password = Scan<int64_t>();
		if (password < 0 || password > 2147483647) {
    		Print("Invalid password."s);
    		continue;
		}
        Customer customer(account_number, password);

        if (!bankService.ValidateCustomer(customer)) {
            Print("Invalid account number or password."s);
            continue;
        }

        auto user = bankService.GetCustomer(account_number);
        Print("Welcome "s + user->GetLongName() + "!"s);

		while (true) {
		user = bankService.GetCustomer(account_number);
        Print("Please select an option:");
        Print("1. Deposit");
        Print("2. Withdraw");
        Print("3. Transfer");
        Print("4. Check Balance");
        Print("5. Exit");

        auto option = Scan<int>();
		
        switch (option) {
            case 1: {
                Print("Please enter the amount you would like to deposit: ");
                auto amount = Scan<int>();
                if (amount < 0) {
                    Print("Invalid amount."s);
                    break;
                }
				bankService.Deposit(*user, amount);
                Print("Deposit successful!"s);
                break;
            }
            case 2: {
                Print("Please enter the amount you would like to withdraw: ");
                auto amount = Scan<int>();
                if (amount < 0) {
                    Print("Invalid amount."s);
                    break;
                }
				bankService.Withdraw(*user, amount);
                Print("Withdrawal successful!"s);
                break;
            }
            case 3: {
                Print("Please enter the account number you would like to transfer to: ");
                auto receiverAccNum = Scan<int>();
                Print("Please enter the amount you would like to transfer: ");
                auto amount = Scan<int>();
                if (amount < 0) {
                    Print("Invalid amount."s);
                    break;
                }

                if(!bankService.TransferMoney(user->GetAccountNumber(), receiverAccNum, amount)) {
                    Print("Transfer failed."s);
                    break;
                }
                Print("Transfer successful!"s);
                break;
            }
            case 4: {
                Print("Your balance is: "s + std::to_string(user->GetBalance()));
                break;
            }
            case 5: {
                Print("Thank you for using Bank Easy!"s);
                return 0;
            }
            default: {
                Print("Invalid option."s);
                break;
            }
        }
    }
	}
}