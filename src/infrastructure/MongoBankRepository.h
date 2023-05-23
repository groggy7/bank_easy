#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <fmt/core.h>
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
    void AddCustomer(Customer& customer) override {
        
    }

    std::vector<Customer> GetCustomers() override {
        //mongocxx::v_noabi::database db = GetDatabase();
        auto collection = database["customers"];
        auto cursor_all = collection.find({});
        std::vector<Customer> customers;

        for (auto &&doc : cursor_all)
        {
            Customer customer;
            for (auto &&element : doc)
            {
                if (element.key() == "long_name")
                {
                    customer.SetLongName(std::string(element.get_string()));
                }
                else if (element.key() == "password")
                {
                    customer.SetPassword(element.get_int32().value);
                }
                else if (element.key() == "balance")
                {
                    customer.SetBalance(element.get_int64().value);
                }
                else if (element.key() == "account_number")
                {
                    customer.SetAccountNumber(element.get_int64().value);
                }
                else if (element.key() == "phone_number")
                {
                    customer.SetPhoneNumber(element.get_int64().value);
                }
            }
            customers.emplace_back(customer);
    }
    return customers;
    }

    void RemoveCustomer(Customer& customer) override {
        
    }

    bool ValidateCustomer(Customer& customer) override {
       return true;
    }

    void TransferMoney(Customer& sender, Customer& receiver, double amount) override {
       
    }

private:
    mongocxx::v_noabi::database database;
};
