# Warehouse Inventory Management System

A C++ application for managing warehouse stock, built as coursework for a Software Development and Implementation module (BSc Computer Science with Artificial Intelligence, Nottingham Trent University).

## Features

- Add, update, remove and search inventory items
- Persistent storage using CSV files
- Input validation and exception handling for invalid operations
- Unit tests covering core behaviour

## Architecture

The project follows a layered design to keep responsibilities separate:

| Layer | Responsibility |
|-------|----------------|
| Domain | Core entities such as items and stock records |
| Repository | Loading and saving data (CSV) |
| Service | Business rules and operations |
| Controller | Coordinates user actions and services |
| UI | Console interface |

The design phase produced use case, sequence, state, class and component UML diagrams.

## Technologies

- C++ (STL containers and algorithms)
- CMake
- CLion

## Project structure

```
SRC/              Source code
TESTS/            Test code
BUILD/            CMake build configuration
CMakeLists.txt    Project build file
```

## Build and run

Requires a C++ compiler and CMake (3.10 or later).

```bash
git clone https://github.com/linabelaa-eng/warehouse-inventory-cpp.git
cd warehouse-inventory-cpp
cmake -S . -B build
cmake --build build
```

Then run the executable from the `build` folder.

## What I learned

- Designing a layered architecture and documenting it with UML
- Using STL containers and reasoning about time complexity
- Handling errors with exceptions
- Structuring a CMake project with separate source and test code

## Author

Lina Belaa, Computer Science with AI student at Nottingham Trent University
