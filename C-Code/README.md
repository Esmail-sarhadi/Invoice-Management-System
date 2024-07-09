
## C Invoice Management System

### Description

This is a simple C-based invoice management system. It allows users to manage products, add new invoices, view invoices by date, find the date with the most customers, identify the best-selling day, view product prices, and view monthly and annual income.

### Requirements

- GCC Compiler

### Files

- `main.c`: The main C program file containing the invoice management system logic.
- `products.txt`: A file to store product information.
- `invoices.txt`: A file to store invoice information.

### Compilation and Execution

1. **Clone the repository or download the script files.**

2. **Open a terminal and navigate to the directory containing `main.c`.**

3. **Compile the program using GCC:**

   ```sh
   gcc main.c -o invoice_management
   ```

4. **Run the compiled program:**

   ```sh
   ./invoice_management
   ```

5. **Follow the on-screen menu to interact with the system.**

### Menu Options

1. **Add New Invoice**
2. **Add New Product**
3. **View Invoices by Date**
4. **Find Date with Most Customers**
5. **Find Best Selling Day**
6. **View Product Price**
7. **View Monthly and Annual Income**
8. **Exit**

---

### Note

- Ensure `products.txt` and `invoices.txt` files are in the same directory as the script or executable to avoid file not found errors.
- The data format in `products.txt` and `invoices.txt` should be consistent with the expected format in the scripts.

### Example Data Format

**products.txt:**
```
1-ProductA-100
2-ProductB-200
```

**invoices.txt:**
```
1-2024/07/10-2 1 5 2 3
2-2024/07/11-1 2 10
