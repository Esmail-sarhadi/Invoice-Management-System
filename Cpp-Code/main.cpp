#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct Product {
    int code;
    string name;
    int price;
};

struct Invoice {
    int number;
    string date;
    vector<pair<int, int>> items; // pair<product_code, quantity>
};

vector<Product> products;
vector<Invoice> invoices;

// Function to check and create file if it doesn't exist
void checkAndCreateFile(const string &filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Unable to create file: " << filename << endl;
    }
    file.close();
}

// Function to load products from file
void loadProducts(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open products file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Product product;
        string code, price;
        getline(ss, code, '-');
        getline(ss, product.name, '-');
        getline(ss, price, '-');
        product.code = stoi(code);
        product.price = stoi(price);
        products.push_back(product);
    }
    file.close();
}

// Function to load invoices from file
void loadInvoices(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open invoices file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Invoice invoice;
        string number, date, itemCount;
        getline(ss, number, '-');
        getline(ss, date, '-');
        getline(ss, itemCount, '-');
        invoice.number = stoi(number);
        invoice.date = date;
        int count = stoi(itemCount);
        for (int i = 0; i < count; ++i) {
            int productCode, quantity;
            ss >> productCode >> quantity;
            invoice.items.push_back({productCode, quantity});
        }
        invoices.push_back(invoice);
    }
    file.close();
}

// Function to add a new product
void addProduct(const Product &product, const string &filename) {
    products.push_back(product);
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Unable to open products file for writing: " << filename << endl;
        return;
    }
    file << product.code << "-" << product.name << "-" << product.price << endl;
    file.close();
}

// Function to add a new invoice
void addInvoice(const Invoice &invoice, const string &filename) {
    invoices.push_back(invoice);
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Unable to open invoices file for writing: " << filename << endl;
        return;
    }
    file << invoice.number << "-" << invoice.date << "-" << invoice.items.size();
    for (const auto &item : invoice.items) {
        file << " " << item.first << " " << item.second;
    }
    file << endl;
    file.close();
}

// Function to view invoices of a specific date
void viewInvoicesByDate(const string &date) {
    for (const auto &invoice : invoices) {
        if (invoice.date == date) {
            cout << "Shomare Faktor: " << invoice.number << endl;
            for (const auto &item : invoice.items) {
                cout << "Code Mahsol: " << item.first << ", Tedad: " << item.second << endl;
            }
        }
    }
}

// Function to find the date with most customers
void findDateWithMostCustomers() {
    map<string, int> customerCount;
    for (const auto &invoice : invoices) {
        customerCount[invoice.date]++;
    }

    string mostPopularDate;
    int maxCount = 0;
    for (const auto &entry : customerCount) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mostPopularDate = entry.first;
        }
    }
    cout << "Tarikh ba bishtarin moshtari: " << mostPopularDate << endl;
}

// Function to find the best selling day
void findBestSellingDay() {
    map<string, int> salesCount;
    for (const auto &invoice : invoices) {
        for (const auto &item : invoice.items) {
            salesCount[invoice.date] += item.second;
        }
    }

    string bestSellingDate;
    int maxSales = 0;
    for (const auto &entry : salesCount) {
        if (entry.second > maxSales) {
            maxSales = entry.second;
            bestSellingDate = entry.first;
        }
    }
    cout << "Behtarin rooz: " << bestSellingDate << endl;
}

// Function to view the price of a specific product
void viewProductPrice(int productCode) {
    for (const auto &product : products) {
        if (product.code == productCode) {
            cout << "Gheymat " << product.name << ": " << product.price << endl;
            return;
        }
    }
    cout << "Mahsol peyda nashod." << endl;
}

// Function to view annual and monthly income
void viewIncome() {
    map<string, int> monthlyIncome;
    map<string, int> annualIncome;

    for (const auto &invoice : invoices) {
        int totalAmount = 0;
        for (const auto &item : invoice.items) {
            for (const auto &product : products) {
                if (product.code == item.first) {
                    totalAmount += product.price * item.second;
                }
            }
        }

        string month = invoice.date.substr(0, 7); // "yyyy/mm"
        string year = invoice.date.substr(0, 4); // "yyyy"
        monthlyIncome[month] += totalAmount;
        annualIncome[year] += totalAmount;
    }

    cout << "Daramad Mahane:" << endl;
    for (const auto &entry : monthlyIncome) {
        cout << entry.first << ": " << entry.second << endl;
    }

    cout << "Daramad Salane:" << endl;
    for (const auto &entry : annualIncome) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

void showMenu() {
    cout << "Menue:" << endl;
    cout << "1. Darj Faktore Jadid" << endl;
    cout << "2. Darj Mahsol Jadid" << endl;
    cout << "3. Moshahede Faktorehaye yek rooz moshakhas" << endl;
    cout << "4. Moshahede tarikh rooz ba bishtarin moshtari" << endl;
    cout << "5. Moshahede pforush tarin rooz sal" << endl;
    cout << "6. Moshahede gheymat yek mahsol khas" << endl;
    cout << "7. Moshahede daramad salane va mahane" << endl;
    cout << "8. Khorooj" << endl;
    cout << "Lotfan yek gozine ra entekhab konid: ";
}

int main() {
    // Check and create files if they don't exist
    checkAndCreateFile("products.txt");
    checkAndCreateFile("invoices.txt");

    // Load data from files
    loadProducts("products.txt");
    loadInvoices("invoices.txt");

    int choice;
    while (true) {
        showMenu();
        cin >> choice;
        if (choice == 8) {
            break;
        }

        switch (choice) {
            case 1: {
                Invoice newInvoice;
                cout << "Shomare Faktor: ";
                cin >> newInvoice.number;
                cout << "Tarikh (yyyy/mm/dd): ";
                cin >> newInvoice.date;
                int itemCount;
                cout << "Tedad Kala: ";
                cin >> itemCount;
                for (int i = 0; i < itemCount; ++i) {
                    int productCode, quantity;
                    cout << "Code Mahsol va Tedad: ";
                    cin >> productCode >> quantity;
                    newInvoice.items.push_back({productCode, quantity});
                }
                addInvoice(newInvoice, "invoices.txt");
                break;
            }
            case 2: {
                Product newProduct;
                cout << "Code Mahsol: ";
                cin >> newProduct.code;
                cout << "Name Mahsol: ";
                cin >> newProduct.name;
                cout << "Gheymat Mahsol: ";
                cin >> newProduct.price;
                addProduct(newProduct, "products.txt");
                break;
            }
            case 3: {
                string date;
                cout << "Tarikh (yyyy/mm/dd): ";
                cin >> date;
                viewInvoicesByDate(date);
                break;
            }
            case 4: {
                findDateWithMostCustomers();
                break;
            }
            case 5: {
                findBestSellingDay();
                break;
            }
            case 6: {
                int productCode;
                cout << "Code Mahsol: ";
                cin >> productCode;
                viewProductPrice(productCode);
                break;
            }
            case 7: {
                viewIncome();
                break;
            }
            default: {
                cout << "Gozine eshtebah ast. Dobare emtehan konid." << endl;
                break;
            }
        }
    }

    return 0;
}
