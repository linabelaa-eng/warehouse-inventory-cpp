# Warehouse Inventory System – Program Logic and Flow

## 1. Program Entry Point

```
main() → WarehouseSystem() → loadData() → run()
```

1. **main.cpp** creates a `WarehouseSystem` object, calls `loadData()`, then `run()`.
2. The program runs until the user closes it (or an exception occurs).

---

## 2. Startup Flow (loadData)

```
loadData()
├── Try to load users from Testing/users.csv
├── If users loaded AND not empty:
│   ├── Ensure admin exists (create if missing, fix hash if wrong)
│   ├── Load products (Testing/products.csv)
│   ├── Load employees (Testing/employees.csv)
│   ├── Load orders (Testing/orders.csv + order_items.csv)
│   └── Show "Loaded from data files..."
└── Else (no users or load failed):
    ├── Create default admin + manager2–5 (password: admin)
    ├── Create 50 employees (password: employee)
    ├── Create 100 products, 50 employees, 67 orders
    └── Save everything to CSV files
```

**Data directory:** All CSV files are in `Testing/` (relative to the working directory).

---

## 3. Main Loop (run)

```
run()
└── while (true)
    └── runLoginAndMenuLoop()
        ├── Show login screen
        ├── If login fails → show error, return to login
        └── If login succeeds → show Manager or Employee menu loop
```

The main loop keeps showing the login screen until login succeeds, then runs menus until logout.

---

## 4. Login Flow (runLoginAndMenuLoop)

```
1. Display login box (Username, Password)
2. Read username and password
3. authManager_->login(user, pass)
   ├── Look up username in users_ map
   ├── Hash the entered password (djb2-style algorithm)
   ├── Compare with stored hash
   └── Return User* if match, nullptr if not
4. If login fails → "Invalid username or password", return
5. If login succeeds:
   ├── Show welcome message
   ├── If role == "Manager" → showManagerMenu() loop
   └── If role == "Employee" → showEmployeeMenu() loop
6. On logout: saveData(), clear currentUser_, show goodbye, return to login
```

**Login logic:** Passwords are stored as hashes in `users.csv`. `AuthManager::login()` hashes the input and compares it to the stored hash. After 3 failed attempts, the program exits.

---

## 5. Manager Flow

```
showManagerMenu()
├── 1. Products → productManagement()
│   ├── Add product (id, name, qty, aisle, shelf, price)
│   ├── View all products
│   └── Edit product
├── 2. Employees → employeeManagement()
│   ├── Add employee (id, name) + optional login account
│   ├── View all employees
│   └── Edit employee name
├── 3. Orders → orderManagement()
│   ├── Create order (id + line items: productId, quantity)
│   ├── View all orders
│   └── Edit order (re-add items; completed orders cannot be edited)
├── 4. Assign order → assignOrder()
│   └── Assign order to employee (sets status to InProgress)
├── 5. Reports → reportMenu()
│   ├── Inventory report (all products → CSV)
│   ├── Completed orders report (status=Completed → CSV)
│   └── Pending orders report (status=Pending or InProgress → CSV)
└── 6. Logout → currentUser_ = nullptr (exits menu loop)
```

**Data changes:** Each add/edit/assign/complete triggers `saveData()` so the CSV files stay up to date.

---

## 6. Employee Flow

```
showEmployeeMenu()
├── 1. My orders → viewAssignedOrders()
│   └── List orders where assignedEmployeeId == current user's employeeId
├── 2. Complete order → completeOrder()
│   ├── Check order exists, assigned to you, not already completed
│   ├── Check sufficient stock (canFulfillOrder)
│   ├── deductStock() → reduce product quantities
│   └── Set order status to "Completed"
├── 3. Search products → searchProducts()
│   └── Search by product ID or name (partial match)
├── 4. My report → generateMyReport()
│   └── Export assigned orders to CSV
└── 5. Logout → currentUser_ = nullptr
```

---

## 7. Key Data Structures (in memory)

| Variable | Type | Purpose |
|----------|------|---------|
| users_ | map&lt;string, User*&gt; | Login accounts (key = username) |
| products_ | map&lt;string, Product&gt; | Product catalog (key = product ID) |
| employees_ | map&lt;string, EmployeeRecord&gt; | Employee records (key = employee ID) |
| orders_ | map&lt;string, Order&gt; | Orders (key = order ID); each Order has a list of OrderItem |
| currentUser_ | User* | Currently logged-in user |

---

## 8. Class Responsibilities

| Class | Responsibility |
|-------|----------------|
| **WarehouseSystem** | Main controller: menus, orchestration, validation |
| **AuthManager** | Login, password hashing, user lookup (uses `users_`) |
| **FileHandler** | Load/save all CSV files |
| **ReportGenerator** | Build and write report CSV files |
| **Product** | id, name, quantity, aisle, shelf, price, getStockStatus() |
| **Order** | orderId, status, assignedEmployeeId, list of OrderItem |
| **OrderItem** | productId, quantity |
| **EmployeeRecord** | employeeId, name |
| **User** (abstract) | username, passwordHash; Manager and Employee inherit from it |

---

## 9. Order Lifecycle

```
1. Manager creates order → status = "Pending", no employee assigned
2. Manager assigns order → status = "InProgress", assignedEmployeeId set
3. Employee completes order → deductStock(), status = "Completed"
```

**Stock checks:** Before creating or editing an order, and before completing it, `canFulfillOrder()` checks that stock is sufficient for all items. Completed orders cannot be edited.

---

## 10. Data Persistence

**Load:** On startup, `FileHandler` reads from `Testing/*.csv`.

**Save:** `saveData()` writes all maps to CSV. It is called:
- After every add/edit/assign/complete
- On logout

**Files:** users.csv, products.csv, employees.csv, orders.csv, order_items.csv.

---

## 11. Flow Diagram (Simplified)

```
┌─────────────┐
│   main()    │
└──────┬──────┘
       │
       ▼
┌─────────────────┐     ┌──────────────┐
│ WarehouseSystem │────►│  loadData()  │
│   constructor   │     │  (CSV load)  │
└────────┬────────┘     └──────┬───────┘
         │                     │
         ▼                     ▼
┌─────────────────┐     ┌──────────────┐
│     run()       │◄────│  Login screen │
│  (main loop)    │     └──────┬───────┘
└────────┬────────┘            │
         │                      │ login OK
         ▼                      ▼
┌─────────────────────────────────────┐
│  Manager Menu          Employee Menu│
│  - Products            - My orders  │
│  - Employees           - Complete   │
│  - Orders               - Search    │
│  - Assign               - My report  │
│  - Reports              - Logout    │
│  - Logout                            │
└──────────────────┬──────────────────┘
                    │ Logout
                    ▼
            ┌──────────────┐
            │  saveData()  │
            │  (CSV save)  │
            └──────┬───────┘
                   │
                   ▼
            ┌──────────────┐
            │ Login screen │ (loop back)
            └──────────────┘
```
