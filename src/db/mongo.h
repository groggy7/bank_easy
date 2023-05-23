#include "models.h"
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

void PrintDocument(const mongocxx::database db) {
    auto collection = db["customers"];

    auto find_one_filtered_result = collection.find_one(make_document(kvp("password", 140701)));
    if (find_one_filtered_result)
    {
        auto doc_view = find_one_filtered_result.value().view();

        // Print the document or perform further operations
        for (auto&& element : doc_view) {
            std::cout << element.key() << ": ";

            if (element.type() == bsoncxx::type::k_utf8) {
                //std::string value(element.get_string());
                std::cout << std::string(element.get_string());
            } else if (element.type() == bsoncxx::type::k_int32) {
                std::cout << element.get_int32().value;
            } else if (element.type() == bsoncxx::type::k_int64) {
                std::cout << element.get_int64().value;
            } else if (element.type() == bsoncxx::type::k_double) {
                std::cout << element.get_double().value;
            }
            std::cout << std::endl;
        }
    }
}

std::vector<User> GetCustomers() {
    auto db = GetDatabase();
    auto collection = db["customers"];
    auto cursor_all = collection.find({});
    std::vector<User> users;
    
    for (auto&& doc : cursor_all) {
        User user;
        for (auto&& element : doc) {
            if(element.key() == "long_name") {
                user.name = std::string(element.get_string());
            } else if(element.key() == "password") {
                user.password = element.get_int32().value;
            } else if (element.key() == "balance") {
               user.balance = element.get_int64().value;
            } else if (element.key() == "account_number") {
                user.account_number = element.get_int64().value;
            } else if (element.key() == "phone_number") {
                user.phone_number = element.get_int64().value;
            }
        }
        users.emplace_back(user);
    }
    return users;
}