cmake_minimum_required(VERSION 4.0)
project(Warehouse)

set(CMAKE_CXX_STANDARD 20)

add_executable(Warehouse src/main.cpp
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
        include/AUTHMANAGER.h
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
