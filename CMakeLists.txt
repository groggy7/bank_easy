cmake_minimum_required(VERSION 3.22.1)
project(bank_easy)

set(SOURCES
    src/main.cpp
    src/domain/customer.h
    src/infrastructure/MongoBankRepository.h
    src/infrastructure/IBankRepository.h
    src/application/BankService.h
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(bsoncxx REQUIRED)
find_package(mongocxx REQUIRED)

add_executable(bank_easy ${SOURCES})

target_link_libraries(bank_easy PRIVATE /usr/local/lib/libmongocxx.so)
target_link_libraries(bank_easy PRIVATE /usr/local/lib/libbsoncxx.so)

target_include_directories(bank_easy
    PRIVATE /usr/local/include/mongocxx/v_noabi
    PRIVATE /usr/local/include/bsoncxx/v_noabi
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
