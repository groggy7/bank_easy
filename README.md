# BANK EASY

Bank Easy is a console-based bank application written in C++ that allows users to perform banking operations. It leverages MongoDB  as the database to store customer information and transaction data.

## Features

* [x] User-friendly console interface for interacting with the bank application.
* [x] Deposit and withdraw funds from customer accounts.
* [x] Transfer funds between customer accounts.

## Planned Features 
- [ ] Customer management: Create, update, and delete customer accounts.
- [ ] Account management: Open, close, and view account details (e.g., balance, transaction  history).

## Prerequisites

Before running the application, make sure you have the following dependencies installed:

#### Windows

* C++ compiler that supports C++17
* [CMake](https://cmake.org/) build system
* [vcpkg](https://github.com/microsoft/vcpkg) package manager
* MongoDB C++ Driver
* MongoDB Atlas account or a local MongoDB server

Installing MongoDB C++ Driver with vcpkg:
1. Install vcpkg by following the official [vcpkg installation guide](https://github.com/microsoft/vcpkg#quick-start-windows).
2. Open a command prompt and run the following command to integrate vcpkg with your environment:  

    ```shell
    vcpkg integrate install
    ```
3. Install the MongoDB C++ Driver using vcpkg:
    ```shell
    vcpkg install mongo-cxx-driver
    ```
4. Note down the installation path provided by vcpkg after the installation completes. You will need this path in the CMake configuration.

#### Linux

* C++ compiler that supports C++17.
* [CMake](https://cmake.org/) build system.
* Libmongoc (The mongocxx driver builds on top of the MongoDB C driver.) [How to install libmongoc](http://mongoc.org/libmongoc/current/installing.html)

Installing MongoDB C++ Driver for linux:

1. **Download the latest version of the mongocxx driver:**
    ```shell
    curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.7.1/mongo-cxx-driver-r3.7.1.tar.gz
    tar -xzf mongo-cxx-driver-r3.7.1.tar.gz
    cd mongo-cxx-driver-r3.7.1/build
    ```
2. **Configure the driver:**
On Unix systems, libmongoc installs into /usr/local by default. To configure mongocxx for installation into /usr/local as well, use the following cmake command:
    ```shell
    cmake ..                                \
        -DCMAKE_BUILD_TYPE=Release          \
        -DCMAKE_INSTALL_PREFIX=/usr/local
    ```
3. **Build and install the driver:**
If you are using the default MNMLSTC polyfill and are installing to a directory requiring root permissions, you should install the polyfill with sudo before building the rest of mongocxx so you don’t have to run the entire build with sudo:
    ```shell
    # Only for MNMLSTC polyfill
    sudo cmake --build . --target EP_mnmlstc_core
    ```
    Once MNMLSTC is installed, or if you are using a different polyfill, build and install the driver:
    ```shell
    cmake --build .
    sudo cmake --build . --target install
    ```
    If you have problems building the mongocxx driver, you can find additional information on the [official page](https://mongocxx.org/mongocxx-v3/installation/linux/).


## Installation & Usage
1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/groggy7/bank_easy
   ```
2. Update the connection details in the application code:
    * Open the file src/infrastructure/MongoBankRepository.h.
    * Update the MongoDB connection string with your MongoDB Atlas or local server details.

3. Configure the Database: 
Create a database named 'bank_easy'. You can use alternative names, but please remember to update the code accordingly to reflect the chosen name. Then import the provided [collection](https://www.dropbox.com/sh/4ehxkz3sjhx3t27/AAAo-L07qqfyvhcFDh4W11pJa?dl=0). I have uploaded the collection in both JSON and CSV formats, you can import the one you prefer.

4. Build the application using CMake:
    ```shell
    cd bank-easy
    mkdir build && cd build
    cmake ..
    make
    ```

5. Run the compiled application:
The code provided in Step 4 will generate the executable file named 'bank_easy'. You can now run it: 
    ```shell
    ./bank_easy
    ```
