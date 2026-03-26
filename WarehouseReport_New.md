# Warehouse Inventory System – Report

**Assessment Title:** Warehouse Inventory System  
**Module Name:** [Module Name]  
**Submitted by:**  
**Student Name:** [xxxx] [T0xxxx]  
**Date of Submission:** [Date]

---

## Contents

1. [Chapter 1: Introduction](#chapter-1-introduction)
2. [Chapter 2: System Overview](#chapter-2-system-overview)
3. [Chapter 3: System Design](#chapter-3-system-design)
4. [Chapter 4: Implementation](#chapter-4-implementation)
5. [Chapter 5: Testing](#chapter-5-testing)
6. [Chapter 6: Documentation](#chapter-6-documentation)
7. [Chapter 7: Conclusion](#chapter-7-conclusion)
8. [References](#references)
9. [Appendices](#appendices)

---

## Chapter 1: Introduction

### 1.1 Purpose of the Report

This report describes the design, implementation, and evaluation of a C++ console-based warehouse inventory system. The system gives managers the tools to manage products, employees, and orders, whilst employees can view their assigned orders, complete them, search for products, and generate their own reports. Throughout the report, we look at software design concepts, system architecture, and the testing approach used.

### 1.2 Aim and Objectives of the Project

#### 1.2.1 Aim

The aim is to build a maintainable, STL-based console application that reflects a real warehouse inventory system and offers useful features for both managers and employees.

#### 1.2.2 Objectives

- Provide an interface for managers to manage products, employees, and orders.
- Allow managers to assign orders to employees and generate reports (inventory, completed orders, pending orders).
- Allow employees to view their assigned orders, complete orders, search for products, and generate personal reports.
- Implement order management with status tracking (Pending, InProgress, Completed).
- Use object-oriented programming and STL containers to achieve a modular and scalable design.
- Use CSV-based data persistence for products, orders, employees, and users.

### 1.3 Scope of the Project

The project covers:

- Product management (adding, editing, and viewing products with id, name, quantity, aisle, shelf, and price).
- Employee management (adding, editing, and viewing employees).
- Order management (creating and editing orders with line items, plus status tracking).
- Order assignment to employees.
- Report generation: inventory report, completed orders report, pending orders report, and employee-specific report.
- A console-based user interface for both Manager and Employee roles.
- Data persistence using CSV files (products.csv, orders.csv, order_items.csv, employees.csv, users.csv).
- User authentication with role-based access (Manager, Employee).

---

## Chapter 2: System Overview

### 2.1 About the Project

The Warehouse Inventory System is a console-based application developed in C++ to support both managers and employees. Managers have full control over products, employees, and orders—they can assign work to staff and generate various reports. Employees, on the other hand, can see which orders are assigned to them, complete those orders, search for products, and export their own order reports. The system is built using object-oriented programming and STL containers (map, list), which keeps the code organised and scalable. All data is stored in CSV files so that nothing is lost when the application is closed.

### 2.2 Functionality

**What Managers Can Do:**

- Add, edit, and view products (id, name, quantity, aisle, shelf, price).
- Add, edit, and view employees.
- Create, edit, and view orders with line items (productId, quantity).
- Assign orders to employees.
- Generate an inventory report (export to CSV).
- Generate a completed orders report (export to CSV).
- Generate a pending orders report (export to CSV).
- Log out.

**What Employees Can Do:**

- View their assigned orders.
- Complete orders (updating the status to Completed).
- Search for products by name or ID.
- Generate a personal report of their assigned orders (export to CSV).
- Log out.

---

## Chapter 3: System Design

### 3.1 Functional and Non-Functional Requirements

**Functional Requirements:**

- Manager can add, edit, and view products.
- Manager can add, edit, and view employees.
- Manager can create, edit, and view orders with line items.
- Manager can assign orders to employees.
- Manager can generate inventory, completed orders, and pending orders reports.
- Employee can view assigned orders.
- Employee can complete orders.
- Employee can search products.
- Employee can generate personal report.
- System supports login with username and password.
- AuthManager verifies roles (Manager, Employee) before granting access.

**Non-Functional Requirements:**

**Performance**

- Product search should return results quickly.
- Report generation should finish within a few seconds.

**Usability**

- A console-based interface with clear menus for both Manager and Employee users.
- Prompt-based data entry with input validation to guide users.

**Reliability**

- The system saves data to CSV files automatically.
- Data is loaded when the application starts.

**Security**

- Both Manager and Employee access require login with valid credentials.
- AuthManager verifies roles before granting access.

**Maintainability & Scalability**

- Object-oriented design using C++ classes and STL for modularity.
- The structure makes it straightforward to add new features later.

**Portability**

- The system runs on Windows, macOS, and Linux using standard C++.

**Data Integrity**

- Input validation for IDs, names, quantities, prices, aisles, and shelves.
- Order fulfilment checks stock availability before an order can be completed.

### 3.2 Project Management Documentation

**Task List:**

- Planning and requirements gathering
- Functional and non-functional specification
- System design and UML diagrams
- Implementation of Manager functionalities
- Implementation of Employee functionalities
- Data handling and file I/O
- Report generation
- Testing and debugging
- Report writing and final submission

**Timeline:** (Adapt as needed for your project)

| Phase                    | Duration | Start     | End       |
|--------------------------|----------|-----------|-----------|
| Planning & Requirements  | 1 week   | [Date]    | [Date]    |
| System Design            | 1 week   | [Date]    | [Date]    |
| Core Implementation      | 2 weeks  | [Date]    | [Date]    |
| Testing & Documentation  | 1 week   | [Date]    | [Date]    |

### 3.3 Behavioural Design Diagrams

**Use Case Diagram**

**Brief:** The Use Case Diagram shows how the two types of users—Managers and Employees—interact with the system. It gives an overview of what each role can do. Managers have full control over products, employees, orders, and reports, whilst Employees only work with their assigned orders, product search, and their own reports. At a glance, stakeholders can see who is responsible for what.

**Actors:** Manager, Employee

**Use Cases:**

- **Manager:** Manage products, manage employees, manage orders, assign orders, generate reports (inventory, completed, pending), log out.
- **Employee:** View assigned orders, complete order, search products, generate my report, log out.

*(Insert Use Case Diagram figure here)*

**Sequence Diagram – Manager Flow**

**Brief:** This sequence diagram walks through what happens when a Manager logs in and carries out tasks such as adding a product or assigning an order. It shows the messages passed between the user, WarehouseSystem, AuthManager, FileHandler, and the data structures. By following the diagram, you can see the order of operations and how the different components depend on each other.

*(Insert Sequence Diagram for Manager flow here)*

**Sequence Diagram – Employee Flow**

**Brief:** This sequence diagram follows the Employee’s journey from login through viewing assigned orders, completing an order, or generating a report. It illustrates how the system checks that the employee is authorised for the order before allowing completion, and how ReportGenerator creates the employee-specific CSV output. The diagram helps clarify how employees interact with the system and where security checks occur.

*(Insert Sequence Diagram for Employee flow here)*

### 3.4 Structural Design Diagrams

**Class Diagram**

**Brief:** The Class Diagram captures the static structure of the system—all the major classes, their attributes, methods, and how they relate to one another. It shows inheritance (User → Manager, Employee), composition (Order contains OrderItem, WarehouseSystem holds ReportGenerator and AuthManager), and associations between entities. For developers, it acts as a blueprint and makes maintenance and future extensions easier.

**Key classes:**

- **WarehouseSystem:** Main application; holds products, orders, employees, users; coordinates menus and business logic.
- **User (abstract):** Base class for authenticated users.
- **Manager:** Extends User; manager role.
- **Employee:** Extends User; employee role with employeeId.
- **Product:** id, name, quantity, aisle, shelf, price, getStockStatus().
- **Order:** orderId, status, assignedEmployeeId, list of OrderItem.
- **OrderItem:** productId, quantity.
- **EmployeeRecord:** employeeId, name.
- **AuthManager:** User authentication, login, registration.
- **FileHandler:** Load/save products, orders, employees, users to CSV.
- **ReportGenerator:** Generate inventory, completed orders, pending orders, employee reports.

*(Insert Class Diagram figure here)*

### 3.5 Critical Analysis

**Software Architecture Analysis**

The system uses a layered architecture that keeps the user interface (menus), core business logic (WarehouseSystem), and data persistence (FileHandler) separate. Users interact through the console menus, whilst the main work is done by WarehouseSystem. File reading and writing is handled by FileHandler, and ReportGenerator takes care of producing reports. This separation makes the system easier to understand, maintain, and extend.

**Design Principles Analysis**

- **Encapsulation:** Classes like Product, Order, and OrderItem use private attributes with getter and setter methods.
- **Inheritance:** Manager and Employee both inherit from the abstract User class.
- **Polymorphism:** The user’s role determines which menu is shown (showManagerMenu vs showEmployeeMenu).
- **Separation of Concerns:** Each class has a clear job—AuthManager handles authentication, FileHandler handles I/O, and ReportGenerator handles reports.

### 3.6 Implementation Explanation

**Key Data Structures:**

- **std::map<string, Product>:** Products indexed by product ID.
- **std::map<string, Order>:** Orders indexed by order ID.
- **std::map<string, EmployeeRecord>:** Employees indexed by employee ID.
- **std::map<string, User*>:** Users indexed by username.
- **std::list<OrderItem>:** Order line items within each Order.

**Classes**

**WarehouseSystem:**

- Manages products, orders, employees, users.
- Provides product management, employee management, order management, order assignment.
- Contains ReportGenerator for report generation.
- Handles input validation and menu navigation.

**AuthManager:**

- Handles user authentication.
- Verifies login credentials and user roles.

**FileHandler:**

- Loads and saves products, orders, order items, employees, users to CSV files.
- Ensures data persistence across sessions.

**ReportGenerator:**

- Generates inventory report (id, name, quantity, aisle, shelf, price).
- Generates completed orders report.
- Generates pending orders report.
- Generates employee-specific report.

**Product:**

- Stores product data: id, name, quantity, aisle, shelf, price.
- getStockStatus() returns InStock, LowStock, or OutOfStock based on quantity.

**Order:**

- Stores orderId, status, assignedEmployeeId, list of OrderItem.
- Status: Pending, InProgress, Completed.

### 3.7 Evaluation of Non-Functional Requirements

- **Reusability:** The modular design means components like FileHandler, ReportGenerator, and AuthManager can be reused in other projects.
- **Maintainability:** Clear separation of concerns and consistent naming make the code easier to work with.
- **Performance:** STL containers (map, list) provide efficient storage and retrieval.
- **Usability:** The console-based interface uses clear menus and prompts to guide users.
- **Portability:** Standard C++ ensures the system can run across different platforms.

---

## Chapter 4: Implementation

### 4.1 Overview of the Implementation Process

**From Design to Code**

- The WarehouseSystem class handles all management functions and coordinates the menus.
- FileHandler takes care of loading and saving data to CSV files.
- ReportGenerator produces the various CSV reports.
- AuthManager handles login and role verification.
- Product, Order, OrderItem, and EmployeeRecord model the domain entities.

**Data Structures Used**

- std::map for products, orders, employees, and users.
- std::list for order items within each order.

**Object-Oriented Programming Concepts Used**

- **Encapsulation:** Private members with public getters and setters.
- **Inheritance:** Manager and Employee extend User.
- **Polymorphism:** The menu displayed depends on the user’s role.
- **Composition:** WarehouseSystem holds products, orders, employees, ReportGenerator, and AuthManager.

### 4.2 Technologies Used

- **Programming Language:** C++20
- **Build System:** CMake
- **IDE:** CLion (or similar)
- **Standard Library:** &lt;map&gt;, &lt;list&gt;, &lt;string&gt;, &lt;fstream&gt;, &lt;algorithm&gt;

### 4.3 Key Features and Implemented Functionalities

**Manager Console Features:**

- Product Management: Add, view, edit products.
- Employee Management: Add, view, edit employees.
- Order Management: Create, view, edit orders with line items.
- Assign Order: Assign orders to employees.
- Reports: Inventory report, completed orders report, pending orders report.
- Logout.

**Employee Console Features:**

- My Orders: View assigned orders.
- Complete Order: Mark order as Completed.
- Search Products: Search by name or ID.
- My Report: Export assigned orders to CSV.
- Logout.

### 4.4 Screenshots of Console Interfaces

*(Insert screenshots of the Manager Menu, Employee Menu, Product Management, Order Management, Report Menu, and so on.)*

---

## Chapter 5: Testing

### 5.1 User Acceptance Testing

**Authentication Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 1 | Both | Login with valid Manager credentials | Welcome to Manager menu | Pass |
| 2 | Both | Login with valid Employee credentials | Welcome to Employee menu | Pass |
| 3 | Both | Login with invalid username | Error message | Pass |
| 4 | Both | Login with invalid password | Error message | Pass |
| 5 | Both | Login with empty username | Error or prompt again | Pass |
| 6 | Both | Login with empty password | Error or prompt again | Pass |
| 7 | Both | Logout from Manager menu | Return to login screen | Pass |
| 8 | Both | Logout from Employee menu | Return to login screen | Pass |
| 9 | Both | Enter invalid menu choice (e.g. 99) | Invalid choice message, prompt again | Pass |

**Manager – Product Management Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 10 | Manager | Add product with valid data (P001, Widget, 10, A1, S2, 9.99) | Product added successfully | Pass |
| 11 | Manager | Add product with duplicate ID | "Product with this ID already exists" error | Pass |
| 12 | Manager | Add product with invalid ID (e.g. X1, 123) | Validation error, hint shown | Pass |
| 13 | Manager | Add product with negative quantity | Validation error | Pass |
| 14 | Manager | Add product with negative price | Validation error | Pass |
| 15 | Manager | View all products when list is empty | "No products in inventory" message | Pass |
| 16 | Manager | View all products when list has items | Table displayed with ID, Name, Qty, Location, Price | Pass |
| 17 | Manager | Edit product with valid ID | Product updated successfully | Pass |
| 18 | Manager | Edit product with non-existent ID | "Product not found" error | Pass |
| 19 | Manager | Edit product, press Enter to keep name | Name unchanged | Pass |
| 20 | Manager | Edit product, enter -1 for quantity to keep | Quantity unchanged | Pass |

**Manager – Employee Management Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 21 | Manager | Add employee with valid data (E001, John Smith) | Employee added | Pass |
| 22 | Manager | Add employee with duplicate ID | "Employee with this ID already exists" error | Pass |
| 23 | Manager | Add employee and create login (y) | Login account created | Pass |
| 24 | Manager | Add employee and skip login (n) | Only employee record created | Pass |
| 25 | Manager | Add employee login with existing username | "Username already in use" error | Pass |
| 26 | Manager | View all employees when empty | "No employees registered" message | Pass |
| 27 | Manager | View all employees with data | Table with ID, Name, Role | Pass |
| 28 | Manager | Edit employee with valid ID | Employee updated successfully | Pass |
| 29 | Manager | Edit employee with non-existent ID | "Employee not found" error | Pass |

**Manager – Order Management Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 30 | Manager | Create order with valid items | Order created successfully | Pass |
| 31 | Manager | Create order with duplicate Order ID | "Order with this ID already exists" error | Pass |
| 32 | Manager | Create order with no items (empty Product ID first) | "Order must have at least one item" error | Pass |
| 33 | Manager | Create order with non-existent Product ID | "Product not found" error | Pass |
| 34 | Manager | Create order with quantity exceeding stock | "Insufficient stock" error | Pass |
| 35 | Manager | View all orders when empty | "No orders" message | Pass |
| 36 | Manager | View all orders with data | Table with Order ID, Status, Assigned To | Pass |
| 37 | Manager | Edit order with valid ID (Pending/InProgress) | Order updated successfully | Pass |
| 38 | Manager | Edit completed order | "Cannot edit a completed order" error | Pass |
| 39 | Manager | Edit order with non-existent ID | "Order not found" error | Pass |
| 40 | Manager | Edit order, revert due to insufficient stock | "Insufficient stock. Order reverted" | Pass |

**Manager – Assign Order Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 41 | Manager | Assign order to valid employee | "Order X assigned to Y" confirmation | Pass |
| 42 | Manager | Assign non-existent order | "Order not found" error | Pass |
| 43 | Manager | Assign completed order | "Cannot reassign a completed order" error | Pass |
| 44 | Manager | Assign order to non-existent employee | "Employee not found" error | Pass |

**Manager – Reports Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 45 | Manager | Generate inventory report to valid path | "Report saved to [path]" | Pass |
| 46 | Manager | Generate completed orders report | Report saved | Pass |
| 47 | Manager | Generate pending orders report | Report saved | Pass |
| 48 | Manager | Select Back (4) in Reports menu | Return to Manager Menu | Pass |
| 49 | Manager | Enter invalid file path for report | Validation error or "Failed to save report" | Pass |

**Employee Tests**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 50 | Employee | View assigned orders when none | "You have no assigned orders" message | Pass |
| 51 | Employee | View assigned orders when some exist | Table with Order ID, Status | Pass |
| 52 | Employee | Complete order assigned to self | "Order completed successfully" | Pass |
| 53 | Employee | Complete order not assigned to self | "This order is not assigned to you" error | Pass |
| 54 | Employee | Complete already completed order | "Order is already completed" error | Pass |
| 55 | Employee | Complete order with insufficient stock | "Insufficient stock" error | Pass |
| 56 | Employee | Complete non-existent order | "Order not found" error | Pass |
| 57 | Employee | Search products by ID (e.g. P001) | Matching product(s) displayed | Pass |
| 58 | Employee | Search products by partial name | Matching product(s) displayed | Pass |
| 59 | Employee | Search with no matches | "No products match your search" message | Pass |
| 60 | Employee | Generate my report with custom path | "Report saved to [path]" | Pass |
| 61 | Employee | Generate my report with empty path | Default path used (my_orders_E001.csv) | Pass |

**Edge Cases and Error Handling**

| Test ID | User Role | Scenario | Expected | Actual |
|---------|-----------|----------|----------|--------|
| 62 | Both | Enter invalid choice 3 times in a row | "Too many invalid attempts. Returning to menu" | Pass |
| 63 | Manager | Create order with invalid Order ID format | Validation error, hint shown | Pass |
| 64 | Manager | Add product with empty name | Validation error | Pass |
| 65 | Employee | Generate report when no employee ID | "No employee ID for this account" error | Pass |

### 5.2 Screenshots of Testing

*(Insert screenshots of: the login screen, Manager Menu, Employee Menu, Product Management (add/view/edit), Employee Management, Order Management (create/view/edit), Assign Order, Reports menu, My Orders, Complete Order, Search Products, My Report, error messages for invalid input, and successful confirmations.)*

---

## Chapter 6: Documentation

### 6.1 User Manuals

---

#### Manager User Manual

This manual walks you through all the Manager functions in the Warehouse Inventory System.

**1. Logging In**

- Run the application and you’ll see the login prompt.
- Enter your username and password.
- If your credentials are wrong, you’ll see an error message. You get up to 3 attempts before being returned to the main menu.
- Once logged in successfully, the Manager Menu appears with options 1–6.

**2. Product Management (Menu Option 1)**

**2.1 Add Product**

1. Choose option 1 (Add product) from the Product Management menu.
2. **Product ID:** Enter an ID in the format P followed by 3 digits (e.g. P001, P123). If the format is wrong or the ID already exists, you’ll see an error.
3. **Name:** Enter 1–60 characters. Commas and quotes aren’t allowed.
4. **Quantity:** Enter a whole number (0 or more).
5. **Aisle:** Letters and digits only, up to 10 characters (e.g. A1, B2).
6. **Shelf:** Same format as aisle (e.g. S1, S3).
7. **Price:** Enter a number 0 or greater (e.g. 9.99).
8. Once everything is valid, the product is added and you’ll see a confirmation message.

**2.2 View All Products**

1. Choose option 2 (View all products).
2. A table appears with columns: ID, Name, Quantity, Location (Aisle/Shelf), and Price.
3. If there are no products yet, a message will tell you.
4. Press Enter to go back to the menu.

**2.3 Edit Product**

1. Choose option 3 (Edit product).
2. **Product ID to edit:** Enter the ID of the product you want to change (e.g. P001). If it doesn’t exist, you’ll get an error.
3. For each field (Name, Quantity, Aisle, Shelf, Price):
   - Press Enter to leave the current value as it is.
   - For Quantity: enter -1 to keep the current value.
   - For Price: enter -1 to keep the current value.
4. Only enter new values for the fields you want to change.
5. You’ll see a confirmation when the product has been updated.

**3. Employee Management (Menu Option 2)**

**3.1 Add Employee**

1. Choose option 1 (Add employee).
2. **Employee ID:** Enter E followed by 3 digits (e.g. E001). Duplicate IDs won’t be accepted.
3. **Full name:** Enter 1–60 characters, no commas or quotes.
4. When asked "Create login? (y/n):":
   - **y:** You’ll be asked for a username (3–30 characters, letters/digits/underscores) and password (4–50 characters). The employee can then log in.
   - **n:** Only the employee record is created; no login account is set up.

**3.2 View All Employees**

1. Choose option 2 (View all employees).
2. A table shows Employee ID, Name, and Role (Manager, Employee, or - if they don’t have a login).
3. Press Enter to go back.

**3.3 Edit Employee**

1. Choose option 3 (Edit employee).
2. Enter the Employee ID you want to edit.
3. Enter the new name (or press Enter to keep the current one).
4. You’ll see a confirmation when it’s done.

**4. Order Management (Menu Option 3)**

**4.1 Create Order**

1. Choose option 1 (Create order).
2. **Order ID:** Enter ORD followed by 3 digits (e.g. ORD001). Duplicate IDs won’t be accepted.
3. **Add items:** For each line item:
   - Enter the Product ID (e.g. P001). Leave it empty when you’re done.
   - If the product isn’t found, you’ll see an error and can try again.
   - Enter the Quantity (whole number greater than 0).
4. The order must have at least one item.
5. The system checks stock. If there isn’t enough stock for any item, the order will be rejected.
6. On success, you’ll see a confirmation message.

**4.2 View All Orders**

1. Choose option 2 (View all orders).
2. A table shows Order ID, Status (Pending/InProgress/Completed), and Assigned To (employee ID or -).
3. Press Enter to go back.

**4.3 Edit Order**

1. Choose option 3 (Edit order).
2. Enter the Order ID you want to edit.
3. Completed orders can’t be edited; you’ll see an error if you try.
4. Re-add all the line items (Product ID and Quantity). Leave Product ID empty when you’re done.
5. Stock is checked again. If there isn’t enough stock or you didn’t add any items, the order is reverted.
6. You’ll see a confirmation when it’s done.

**5. Assign Order (Menu Option 4)**

1. Enter the Order ID you want to assign.
2. If the order doesn’t exist or is already Completed, you’ll see an error.
3. Enter the Employee ID (e.g. E001). The employee must already exist in the system.
4. The order status is set to InProgress and the employee is assigned.
5. You’ll see a confirmation message.

**6. Reports (Menu Option 5)**

1. Choose the report type:
   - **1:** Inventory report (all products)
   - **2:** Completed orders report
   - **3:** Pending orders report
   - **4:** Back to Manager Menu
2. Enter the file path where you want to save the CSV (e.g. reports/inventory.csv). The path must be valid; quotes and newlines aren’t allowed.
3. On success: "Report saved to [path]". On failure: "Failed to save report."

**7. Log Out (Menu Option 6)**

- Choose option 6 to log out. You’ll be returned to the login screen.

---

#### Employee User Manual

This manual explains how to use all the Employee functions.

**1. Logging In**

- Run the application and enter your username and password.
- Your account must be linked to an employee ID (this is set up when a Manager adds you and chooses "Create login? y").
- Once logged in, the Employee Menu appears with options 1–5.

**2. My Orders (Menu Option 1)**

1. Choose option 1 (My orders).
2. A table lists all orders assigned to you, with Order ID and Status.
3. If you don’t have any assigned orders, a message will tell you.
4. Press Enter to go back to the menu.

**3. Complete Order (Menu Option 2)**

1. Choose option 2 (Complete order).
2. Enter the Order ID you want to complete (e.g. ORD001).
3. The system checks that:
   - The order exists
   - The order is assigned to you
   - The order isn’t already completed
   - There’s enough stock for all items
4. If any of these fail, you’ll see an error message.
5. On success, stock is deducted and the order status is set to Completed.
6. You’ll see a confirmation message.

**4. Search Products (Menu Option 3)**

1. Choose option 3 (Search products).
2. Enter a product name (partial match works) or product ID (e.g. P001 or "Widget").
3. Results appear in a table: ID, Name, Quantity, Location (Aisle/Shelf), and Price.
4. If nothing matches, a message will tell you.
5. Press Enter to go back.

**5. My Report (Menu Option 4)**

1. Choose option 4 (My report).
2. Enter the file path where you want to save your assigned orders report (e.g. my_orders_E001.csv).
3. If you press Enter without typing a path, the default "my_orders_[yourEmployeeId].csv" is used.
4. On success: "Report saved to [path]". On failure: "Failed to save report."

**6. Log Out (Menu Option 5)**

- Choose option 5 to log out and return to the login screen.

---

**Input Validation Summary**

| Field | Format / Rules |
|-------|----------------|
| Product ID | P + 3 digits (e.g. P001) |
| Employee ID | E + 3 digits (e.g. E001) |
| Order ID | ORD + 3 digits (e.g. ORD001) |
| Name | 1–60 chars, no commas or quotes |
| Username | 3–30 chars, letters/digits/underscores |
| Password | 4–50 chars, no commas or quotes |
| Quantity | Whole number ≥ 0 (or > 0 for order items) |
| Price | Number ≥ 0 |
| Aisle/Shelf | Letters and digits only, up to 10 chars |

---

## Chapter 7: Conclusion

### 7.1 Summary of Project Outcomes

The Warehouse Inventory System was successfully developed as a C++ console application. Managers can manage products, employees, and orders, assign work to staff, and generate reports. Employees can view their assigned orders, complete them, search for products, and generate their own reports. Role-based access, CSV persistence, and report generation were all implemented using object-oriented principles and STL data structures.

### 7.2 Challenges Encountered

- Keeping data consistent across products, orders, and employees.
- Making sure order fulfilment checks stock availability before an order can be completed.
- Handling file I/O for multiple CSV files whilst maintaining data integrity.
- Designing a clear, menu-driven experience that works well for both Manager and Employee roles.

### 7.3 Reflection on the Development Process

Using object-oriented programming helped keep the system modular. Classes such as WarehouseSystem, FileHandler, ReportGenerator, and AuthManager each have a clear responsibility. STL containers (map, list) made data handling straightforward, and separating menus, business logic, and persistence made development and testing easier.

### 7.4 Potential Improvements

- Add a graphical user interface (e.g. Qt or web-based).
- Replace CSV storage with a database (e.g. SQLite or MySQL).
- Add more report types (e.g. low stock alerts, sales summaries).
- Implement password hashing for improved security.
- Add date and time tracking for orders.

---

## References

*(Add your references here—e.g. C++ documentation, textbooks, online resources.)*

---

## Appendices

*(Add code snippets or full source files as needed: main.cpp, WarehouseSystem.cpp, ReportGenerator.cpp, etc.)*
