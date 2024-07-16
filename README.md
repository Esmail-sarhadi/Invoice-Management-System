
# Invoice Management System

This project is a simple invoice management system implemented in C++. It provides functionalities for adding new products, creating invoices, and viewing various reports related to sales and products.

## Features

- **Add New Product**: Allows the user to add a new product with a unique code, name, and price.
- **Create Invoice**: Enables the user to create a new invoice with a specific date and a list of items.
- **View Invoices by Date**: Displays all invoices for a specific date.
- **Find Date with Most Customers**: Identifies the date with the highest number of customers.
- **Find Best Selling Day**: Determines the day with the highest sales.
- **View Product Price**: Shows the price of a specific product based on its code.
- **View Income**: Displays monthly and annual income.

## File Structure

- **main.cpp**: The main source file containing all the code.
- **products.txt**: A text file used to store product information.
- **invoices.txt**: A text file used to store invoice information.

## How to Use

1. **Clone the repository**:
    ```sh
    git clone https://github.com/Esmail-sarhadi/invoice-management-system.git
    ```

2. **Navigate to the project directory**:
    ```sh
    cd invoice-management-system
    ```

3. **Compile the code**:
    ```sh
    g++ -o invoice_system main.cpp
    ```

4. **Run the program**:
    ```sh
    ./invoice_system
    ```

## Menu Options

- **1. Add New Invoice**: Enter invoice number, date, and product details to create a new invoice.
- **2. Add New Product**: Enter product code, name, and price to add a new product.
- **3. View Invoices by Date**: Enter a date to view all invoices for that day.
- **4. Find Date with Most Customers**: Display the date with the highest number of customers.
- **5. Find Best Selling Day**: Show the day with the highest sales.
- **6. View Product Price**: Enter the product code to view its price.
- **7. View Monthly and Annual Income**: Display the income for each month and year.
- **8. Exit**: Exit the program.

## Data Storage

- **Products**: Stored in `products.txt` in the format:
    ```
    code-name-price
    ```
- **Invoices**: Stored in `invoices.txt` in the format:
    ```
    number-date-itemCount productCode1 quantity1 productCode2 quantity2 ...
    ```

## Example

### Adding a Product

1. Select option `2` from the menu.
2. Enter the product code, name, and price.

### Creating an Invoice

1. Select option `1` from the menu.
2. Enter the invoice number, date, and items with their quantities.

### Viewing Invoices by Date

1. Select option `3` from the menu.
2. Enter the date in `yyyy/mm/dd` format.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

<h2 id="donation">Donation</h2>

<p>If you find this project helpful, consider making a donation:</p>
<p><a href="https://nowpayments.io/donation?api_key=REWCYVC-A1AMFK3-QNRS663-PKJSBD2&source=lk_donation&medium=referral" target="_blank">
     <img src="https://nowpayments.io/images/embeds/donation-button-black.svg" alt="Crypto donation button by NOWPayments">
</a></p>
## Contact

For any inquiries or feedback, please contact [sarhadiesmail@gmail.com]
