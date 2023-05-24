cmake_minimum_required(VERSION 3.25.0)
project(bank_easy)

set(SOURCES
    src/main.cpp
    src/domain/customer.h
    src/infrastructure/MongoBankRepository.h
    src/infrastructure/IBankRepository.h
    src/application/BankService.h
    )
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(bank_easy ${SOURCES})
target_include_directories(bank_easy PRIVATE C:/vcpkg/installed/x64-windows/include)
target_link_directories(bank_easy PRIVATE C:/vcpkg/installed/x64-windows/lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
