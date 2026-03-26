# Login and Filing Logic – Explanation

## 1. Login Logic

### Flow
1. **User enters username and password** → `runLoginAndMenuLoop()` calls `readLine()` for both.
2. **AuthManager::login(username, password)** is called:
   - Looks up `username` in the `users_` map (in memory).
   - Hashes the entered password with `hashPassword()` (djb2-style: hash = 5381, then hash = hash * 33 + each character).
   - Compares the hashed password with the stored hash in the User object.
   - Returns the User pointer if they match, or `nullptr` if not.
3. If login succeeds → show Manager or Employee menu.  
   If it fails → show "Invalid username or password" and return to login screen.

### Important
- **Passwords are never stored in plain text.** Only the hash is stored in `users.csv`.
- **AuthManager** holds a pointer to `users_`; it does not load or save files.
- **users_** is filled from `users.csv` at startup by `FileHandler::loadUsers()`.

---

## 2. Filing (Data Persistence) Logic

### Path
- `DATA_DIR = "Testing"` → all CSV files go in the `Testing/` folder (relative to the current working directory).
- Files: `users.csv`, `products.csv`, `employees.csv`, `orders.csv`, `order_items.csv`.

### Load (Startup)
1. `loadData()` creates a `FileHandler` with `DATA_DIR`.
2. `loadUsers()` reads `Testing/users.csv` and fills the `users_` map.
3. If load succeeds and users exist → load products, employees, orders.
4. If load fails or no users → create default users, products, etc., and **save** them.

### Save (When?)
**`saveData()` is now called after every data change:**

| Action | When saved |
|--------|------------|
| Add product | Immediately after adding |
| Edit product | Immediately after updating |
| Add employee | Immediately after adding |
| Create login for employee | Immediately after creating |
| Edit employee | Immediately after updating |
| Create order | Immediately after creating |
| Edit order | Immediately after updating |
| Assign order | Immediately after assigning |
| Complete order | Immediately after completing (stock + status) |
| Log out | On logout (saves any remaining state) |

Data is written to disk right after each change, so nothing is lost if the app closes unexpectedly.
