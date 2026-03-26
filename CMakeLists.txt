cmake_minimum_required(VERSION 3.16)
project(Warehouse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Warehouse
    src/main.cpp
    include/OrderItem.h
    src/OrderItem.cpp
    include/User.h
    src/User.cpp
    include/Product.h
    src/Product.cpp
    include/EmployeeRecord.h
    src/EmployeeRecord.cpp
    include/Order.h
    src/Order.cpp
    include/AuthManager.h
    src/AuthManager.cpp
    include/WarehouseSystem.h
    src/WarehouseSystem.cpp
    src/WarehouseSystemMenus.cpp
    include/Manager.h
    src/Manager.cpp
    include/Employee.h
    src/Employee.cpp
    include/FileHandler.h
    include/ReportGenerator.h
    src/FileHandler.cpp
    src/ReportGenerator.cpp
    src/InputValidator.cpp
)

option(BUILD_TESTS "Build simple unit test runner" ON)
if(BUILD_TESTS)
    add_executable(WarehouseTests
        TESTS/test_main.cpp
        include/OrderItem.h
        src/OrderItem.cpp
        include/User.h
        src/User.cpp
        include/Product.h
        src/Product.cpp
        include/EmployeeRecord.h
        src/EmployeeRecord.cpp
        include/Order.h
        src/Order.cpp
        include/AuthManager.h
        src/AuthManager.cpp
        include/Manager.h
        src/Manager.cpp
        include/Employee.h
        src/Employee.cpp
        include/FileHandler.h
        src/FileHandler.cpp
        include/ReportGenerator.h
        src/ReportGenerator.cpp
        include/WarehouseSystem.h
        src/WarehouseSystem.cpp
        src/WarehouseSystemMenus.cpp
        src/InputValidator.cpp
    )
endif()
