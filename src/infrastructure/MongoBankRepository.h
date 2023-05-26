#include <vector>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/collection.hpp>

#include "IBankRepository.h"
#include "../domain/customer.h"

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

static mongocxx::instance inst{};

mongocxx::client& GetMongoClient() {
    static mongocxx::client conn;
    if (!conn) {
        const auto uri = mongocxx::uri{"mongodb+srv://Groggy7:BSS8gaMBsXtOpA2T@mongo-server.6uq9huv.mongodb.net/?retryWrites=true&w=majority"};
       
        mongocxx::options::client client_options;
        const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
        client_options.server_api_opts(api);
       
        conn = mongocxx::client{uri, client_options};
    }
    return conn;
}

mongocxx::database GetDatabase() {
    mongocxx::client& conn = GetMongoClient();
    return conn["bank_easy"];
}

class MongoBankRepository : public IBankRepository {
public:
    MongoBankRepository() : database(GetDatabase()) {}

    void AddCustomer(const Customer &customer) override
    {
        std::vector<Customer> customers = GetCustomers();
        for (auto &&c : customers)
        {
            if(c.GetLongName() == customer.GetLongName() || c.GetPhoneNumber() == customer.GetPhoneNumber())
            {
                std::cout << "Customer already exists." << std::endl;
                return;
            }
        }

        mongocxx::collection collection = database["customers"];
        bsoncxx::document::value doc = make_document(
            kvp("account_number", bsoncxx::types::b_int64{customer.GetAccountNumber()}),
            kvp("long_name", bsoncxx::types::b_string{customer.GetLongName()}),
            kvp("phone_number", bsoncxx::types::b_int64{customer.GetPhoneNumber()}),
            kvp("password", bsoncxx::types::b_int64{customer.GetPassword()}),
            kvp("balance", bsoncxx::types::b_int64{customer.GetBalance()}));

        try {
        auto insert_one_result = collection.insert_one(std::move(doc));
        }
        catch (const std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    std::optional<Customer> GetCustomer(const int& accNum) override {
        auto collection = database["customers"];
        bsoncxx::document::value filter = make_document(
            kvp("account_number", accNum));

        mongocxx::stdx::optional<bsoncxx::document::value> maybe_result = collection.find_one(std::move(filter));

        if (!maybe_result) {
            return std::nullopt;
        }

        bsoncxx::document::view result_view = maybe_result->view();

        Customer found_customer;
        for (auto &&element : result_view)
        {
            if (element.key().compare("long_name") == 0)
            {
                found_customer.SetLongName(std::string(element.get_string().value.begin(), element.get_string().value.end()));
            }
            else if (element.key().compare("password") == 0)
            {
                found_customer.SetPassword(element.get_int64().value);
            }
            else if (element.key().compare("balance") == 0)
            {
                found_customer.SetBalance(element.get_int64().value);
            }
            else if (element.key().compare("account_number") == 0)
            {
                found_customer.SetAccountNumber(element.get_int64().value);
            }
            else if (element.key().compare("phone_number") == 0)
            {
                found_customer.SetPhoneNumber(element.get_int64().value);
            }
        }
        return found_customer;
    }

    std::vector<Customer> GetCustomers() override {
        auto collection = database["customers"];
        auto cursor_all = collection.find({});
        std::vector<Customer> customers;

        for (auto &&doc : cursor_all)
        {
            Customer customer;
            for (auto &&element : doc)
            {
                if (element.key().compare("long_name") == 0)
                {
                    customer.SetLongName(std::string(element.get_string().value.begin(), element.get_string().value.end()));
                }
                else if (element.key().compare("password") == 0)
                {
                    customer.SetPassword(element.get_int64().value);
                }
                else if (element.key().compare("balance") == 0)
                {
                    customer.SetBalance(element.get_int64().value);
                }
                else if (element.key().compare("account_number") == 0)
                {
                    customer.SetAccountNumber(element.get_int64().value);
                }
                else if (element.key().compare("phone_number") == 0)
                {
                    customer.SetPhoneNumber(element.get_int64().value);
                }
            }
            customers.emplace_back(customer);
    }
    return customers;
    }

    void RemoveCustomer(const Customer& customer) override {
    auto collection = database["customers"];

    bsoncxx::document::value filter = make_document(
        kvp("account_number", customer.GetAccountNumber()));

    mongocxx::stdx::optional<mongocxx::result::delete_result> result = collection.delete_one(std::move(filter));

    if (!result) {
        std::cout << "Failed to delete document." << std::endl;
    }

    std::cout << "Document deleted successfully." << std::endl;
    }

    bool ValidateCustomer(const Customer& customer) override {
       auto customers = GetCustomers();
        for (auto&& c : customers) {
            if (c.GetAccountNumber() == customer.GetAccountNumber() && c.GetPassword() == customer.GetPassword()) {
                return true;
            }
        }
        return false;
    }

    bool TransferMoney(const int& senderAccNum, const int& receiverAccNum, const int& amount) override {
        Customer senderAcc = GetCustomer(senderAccNum).value();
        if (senderAcc.GetBalance() < amount) {
            std::cout << "Insufficient balance." << std::endl;
            return false;
        }

        auto receiver = GetCustomer(receiverAccNum);
        if (!receiver.has_value())
        {
            std::cout << "Receiver account not found." << std::endl;
            return false;
        }

        Customer receiverAcc = receiver.value();
        auto collection = database["customers"];

        auto update_sender = collection.update_one(
            make_document(kvp("account_number", senderAcc.GetAccountNumber())),
            make_document(
                kvp("$set", make_document(kvp("balance", bsoncxx::types::b_int64{senderAcc.GetBalance() - amount})))));

        auto update_reveiver = collection.update_one(
            make_document(kvp("account_number", receiverAcc.GetAccountNumber())),
            make_document(
                kvp("$set", make_document(kvp("balance", bsoncxx::types::b_int64{receiverAcc.GetBalance() + amount})))));
        
        return true;
    }

    void Deposit(const Customer &customer, const int &amount) override {
        auto collection = database["customers"];
        auto update_one_result = collection.update_one(
            make_document(kvp("account_number", customer.GetAccountNumber())),
            make_document(
                kvp("$set", make_document(kvp("balance", bsoncxx::types::b_int64{customer.GetBalance() + amount})))));
    }

    void Withdraw(const Customer& customer, const int& amount) override {
        if (customer.GetBalance() < amount) {
            std::cout << "Insufficient balance." << std::endl;
            return;
        }

        auto collection = database["customers"];
        auto update_one_result = collection.update_one(make_document(kvp("account_number", customer.GetAccountNumber())),
        make_document(
            kvp("$set", make_document(kvp("balance", bsoncxx::types::b_int64{customer.GetBalance() - amount})))));
    }
private:
    mongocxx::v_noabi::database database;
};
