# Build configuration for submission layout (sources live in ../SRC, tests in ../TESTS).

add_executable(Warehouse
    ../SRC/main.cpp
    ../SRC/OrderItem.h
    ../SRC/OrderItem.cpp
    ../SRC/User.h
    ../SRC/User.cpp
    ../SRC/Product.h
    ../SRC/Product.cpp
    ../SRC/EmployeeRecord.h
    ../SRC/EmployeeRecord.cpp
    ../SRC/Order.h
    ../SRC/Order.cpp
    ../SRC/AuthManager.h
    ../SRC/AuthManager.cpp
    ../SRC/WarehouseSystem.h
    ../SRC/WarehouseSystem.cpp
    ../SRC/WarehouseSystemMenus.cpp
    ../SRC/Manager.h
    ../SRC/Manager.cpp
    ../SRC/Employee.h
    ../SRC/Employee.cpp
    ../SRC/FileHandler.h
    ../SRC/ReportGenerator.h
    ../SRC/FileHandler.cpp
    ../SRC/ReportGenerator.cpp
    ../SRC/InputValidator.cpp
)

target_include_directories(Warehouse PRIVATE ${CMAKE_SOURCE_DIR}/SRC)

option(BUILD_TESTS "Build simple unit test runner" ON)
if(BUILD_TESTS)
    add_executable(WarehouseTests
        ../TESTS/test_main.cpp
        ../SRC/OrderItem.h
        ../SRC/OrderItem.cpp
        ../SRC/User.h
        ../SRC/User.cpp
        ../SRC/Product.h
        ../SRC/Product.cpp
        ../SRC/EmployeeRecord.h
        ../SRC/EmployeeRecord.cpp
        ../SRC/Order.h
        ../SRC/Order.cpp
        ../SRC/AuthManager.h
        ../SRC/AuthManager.cpp
        ../SRC/Manager.h
        ../SRC/Manager.cpp
        ../SRC/Employee.h
        ../SRC/Employee.cpp
        ../SRC/FileHandler.h
        ../SRC/FileHandler.cpp
        ../SRC/ReportGenerator.h
        ../SRC/ReportGenerator.cpp
        ../SRC/WarehouseSystem.h
        ../SRC/WarehouseSystem.cpp
        ../SRC/WarehouseSystemMenus.cpp
        ../SRC/InputValidator.cpp
    )
    target_include_directories(WarehouseTests PRIVATE ${CMAKE_SOURCE_DIR}/SRC)
endif()
