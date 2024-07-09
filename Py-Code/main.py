import os

class Product:
    def __init__(self, code, name, price):
        self.code = code
        self.name = name
        self.price = price

class Invoice:
    def __init__(self, number, date):
        self.number = number
        self.date = date
        self.items = []

products = []
invoices = []

def check_and_create_file(filename):
    if not os.path.exists(filename):
        with open(filename, 'w') as file:
            pass

def load_products(filename):
    try:
        with open(filename, 'r') as file:
            for line in file:
                code, name, price = line.strip().split('-')
                products.append(Product(int(code), name, int(price)))
    except FileNotFoundError:
        print(f"Unable to open products file: {filename}")

def load_invoices(filename):
    try:
        with open(filename, 'r') as file:
            for line in file:
                parts = line.strip().split('-')
                invoice = Invoice(int(parts[0]), parts[1])
                item_count = int(parts[2])
                items = parts[3].split()
                for i in range(item_count):
                    product_code = int(items[2 * i])
                    quantity = int(items[2 * i + 1])
                    invoice.items.append((product_code, quantity))
                invoices.append(invoice)
    except FileNotFoundError:
        print(f"Unable to open invoices file: {filename}")

def add_product(product, filename):
    products.append(product)
    with open(filename, 'a') as file:
        file.write(f"{product.code}-{product.name}-{product.price}\n")

def add_invoice(invoice, filename):
    invoices.append(invoice)
    with open(filename, 'a') as file:
        items_str = " ".join(f"{item[0]} {item[1]}" for item in invoice.items)
        file.write(f"{invoice.number}-{invoice.date}-{len(invoice.items)} {items_str}\n")

def view_invoices_by_date(date):
    for invoice in invoices:
        if invoice.date == date:
            print(f"Shomare Faktor: {invoice.number}")
            for item in invoice.items:
                print(f"Code Mahsol: {item[0]}, Tedad: {item[1]}")

def find_date_with_most_customers():
    customer_count = {}
    for invoice in invoices:
        customer_count[invoice.date] = customer_count.get(invoice.date, 0) + 1

    most_popular_date = max(customer_count, key=customer_count.get, default=None)
    print(f"Tarikh ba bishtarin moshtari: {most_popular_date}")

def find_best_selling_day():
    sales_count = {}
    for invoice in invoices:
        for item in invoice.items:
            sales_count[invoice.date] = sales_count.get(invoice.date, 0) + item[1]

    best_selling_date = max(sales_count, key=sales_count.get, default=None)
    print(f"Behtarin rooz: {best_selling_date}")

def view_product_price(product_code):
    for product in products:
        if product.code == product_code:
            print(f"Gheymat {product.name}: {product.price}")
            return
    print("Mahsol peyda nashod.")

def view_income():
    monthly_income = {}
    annual_income = {}

    for invoice in invoices:
        total_amount = 0
        for item in invoice.items:
            for product in products:
                if product.code == item[0]:
                    total_amount += product.price * item[1]

        month = invoice.date[:7]  # "yyyy/mm"
        year = invoice.date[:4]   # "yyyy"
        monthly_income[month] = monthly_income.get(month, 0) + total_amount
        annual_income[year] = annual_income.get(year, 0) + total_amount

    print("Daramad Mahane:")
    for month, amount in monthly_income.items():
        print(f"{month}: {amount}")

    print("Daramad Salane:")
    for year, amount in annual_income.items():
        print(f"{year}: {amount}")

def show_menu():
    print("Menue:")
    print("1. Darj Faktore Jadid")
    print("2. Darj Mahsol Jadid")
    print("3. Moshahede Faktorehaye yek rooz moshakhas")
    print("4. Moshahede tarikh rooz ba bishtarin moshtari")
    print("5. Moshahede pforush tarin rooz sal")
    print("6. Moshahede gheymat yek mahsol khas")
    print("7. Moshahede daramad salane va mahane")
    print("8. Khorooj")
    print("Lotfan yek gozine ra entekhab konid: ", end="")

def main():
    check_and_create_file("products.txt")
    check_and_create_file("invoices.txt")

    load_products("products.txt")
    load_invoices("invoices.txt")

    while True:
        show_menu()
        choice = int(input())
        if choice == 8:
            break

        if choice == 1:
            number = int(input("Shomare Faktor: "))
            date = input("Tarikh (yyyy/mm/dd): ")
            item_count = int(input("Tedad Kala: "))
            items = []
            for _ in range(item_count):
                product_code, quantity = map(int, input("Code Mahsol va Tedad: ").split())
                items.append((product_code, quantity))
            add_invoice(Invoice(number, date, items), "invoices.txt")

        elif choice == 2:
            code = int(input("Code Mahsol: "))
            name = input("Name Mahsol: ")
            price = int(input("Gheymat Mahsol: "))
            add_product(Product(code, name, price), "products.txt")

        elif choice == 3:
            date = input("Tarikh (yyyy/mm/dd): ")
            view_invoices_by_date(date)

        elif choice == 4:
            find_date_with_most_customers()

        elif choice == 5:
            find_best_selling_day()

        elif choice == 6:
            product_code = int(input("Code Mahsol: "))
            view_product_price(product_code)

        elif choice == 7:
            view_income()

        else:
            print("Gozine eshtebah ast. Dobare emtehan konid.")

if __name__ == "__main__":
    main()
