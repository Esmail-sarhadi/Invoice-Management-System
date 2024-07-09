#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_INVOICES 100
#define MAX_ITEMS 100

typedef struct {
    int code;
    char name[50];
    int price;
} Product;

typedef struct {
    int code;
    int quantity;
} Item;

typedef struct {
    int number;
    char date[11];
    int itemCount;
    Item items[MAX_ITEMS];
} Invoice;

Product products[MAX_PRODUCTS];
int productCount = 0;
Invoice invoices[MAX_INVOICES];
int invoiceCount = 0;

void checkAndCreateFile(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Unable to create file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void loadProducts(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open products file: %s\n", filename);
        return;
    }

    while (fscanf(file, "%d-%49[^-]-%d\n", &products[productCount].code, products[productCount].name, &products[productCount].price) != EOF) {
        productCount++;
    }
    fclose(file);
}

void loadInvoices(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open invoices file: %s\n", filename);
        return;
    }

    while (fscanf(file, "%d-%10[^-]-%d", &invoices[invoiceCount].number, invoices[invoiceCount].date, &invoices[invoiceCount].itemCount) != EOF) {
        for (int i = 0; i < invoices[invoiceCount].itemCount; i++) {
            fscanf(file, "%d %d", &invoices[invoiceCount].items[i].code, &invoices[invoiceCount].items[i].quantity);
        }
        invoiceCount++;
    }
    fclose(file);
}

void addProduct(const Product *product, const char *filename) {
    products[productCount++] = *product;
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Unable to open products file for writing: %s\n", filename);
        return;
    }
    fprintf(file, "%d-%s-%d\n", product->code, product->name, product->price);
    fclose(file);
}

void addInvoice(const Invoice *invoice, const char *filename) {
    invoices[invoiceCount++] = *invoice;
    FILE *file = fopen(filename, "a");
    if (!file) {
        fprintf(stderr, "Unable to open invoices file for writing: %s\n", filename);
        return;
    }
    fprintf(file, "%d-%s-%d", invoice->number, invoice->date, invoice->itemCount);
    for (int i = 0; i < invoice->itemCount; i++) {
        fprintf(file, " %d %d", invoice->items[i].code, invoice->items[i].quantity);
    }
    fprintf(file, "\n");
    fclose(file);
}

void viewInvoicesByDate(const char *date) {
    for (int i = 0; i < invoiceCount; i++) {
        if (strcmp(invoices[i].date, date) == 0) {
            printf("Shomare Faktor: %d\n", invoices[i].number);
            for (int j = 0; j < invoices[i].itemCount; j++) {
                printf("Code Mahsol: %d, Tedad: %d\n", invoices[i].items[j].code, invoices[i].items[j].quantity);
            }
        }
    }
}

void findDateWithMostCustomers() {
    int customerCount[MAX_INVOICES] = {0};
    char dates[MAX_INVOICES][11] = {0};
    int uniqueDates = 0;

    for (int i = 0; i < invoiceCount; i++) {
        int found = 0;
        for (int j = 0; j < uniqueDates; j++) {
            if (strcmp(invoices[i].date, dates[j]) == 0) {
                customerCount[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(dates[uniqueDates], invoices[i].date);
            customerCount[uniqueDates]++;
            uniqueDates++;
        }
    }

    int maxCount = 0;
    int maxIndex = 0;
    for (int i = 0; i < uniqueDates; i++) {
        if (customerCount[i] > maxCount) {
            maxCount = customerCount[i];
            maxIndex = i;
        }
    }

    printf("Tarikh ba bishtarin moshtari: %s\n", dates[maxIndex]);
}

void findBestSellingDay() {
    int salesCount[MAX_INVOICES] = {0};
    char dates[MAX_INVOICES][11] = {0};
    int uniqueDates = 0;

    for (int i = 0; i < invoiceCount; i++) {
        int found = 0;
        for (int j = 0; j < uniqueDates; j++) {
            if (strcmp(invoices[i].date, dates[j]) == 0) {
                for (int k = 0; k < invoices[i].itemCount; k++) {
                    salesCount[j] += invoices[i].items[k].quantity;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(dates[uniqueDates], invoices[i].date);
            for (int k = 0; k < invoices[i].itemCount; k++) {
                salesCount[uniqueDates] += invoices[i].items[k].quantity;
            }
            uniqueDates++;
        }
    }

    int maxSales = 0;
    int maxIndex = 0;
    for (int i = 0; i < uniqueDates; i++) {
        if (salesCount[i] > maxSales) {
            maxSales = salesCount[i];
            maxIndex = i;
        }
    }

    printf("Behtarin rooz: %s\n", dates[maxIndex]);
}

void viewProductPrice(int productCode) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].code == productCode) {
            printf("Gheymat %s: %d\n", products[i].name, products[i].price);
            return;
        }
    }
    printf("Mahsol peyda nashod.\n");
}

void viewIncome() {
    int monthlyIncome[MAX_INVOICES] = {0};
    char months[MAX_INVOICES][8] = {0};
    int uniqueMonths = 0;

    int annualIncome[MAX_INVOICES] = {0};
    char years[MAX_INVOICES][5] = {0};
    int uniqueYears = 0;

    for (int i = 0; i < invoiceCount; i++) {
        int totalAmount = 0;
        for (int j = 0; j < invoices[i].itemCount; j++) {
            for (int k = 0; k < productCount; k++) {
                if (products[k].code == invoices[i].items[j].code) {
                    totalAmount += products[k].price * invoices[i].items[j].quantity;
                }
            }
        }

        char month[8] = {0};
        strncpy(month, invoices[i].date, 7); // "yyyy/mm"
        int foundMonth = 0;
        for (int j = 0; j < uniqueMonths; j++) {
            if (strcmp(month, months[j]) == 0) {
                monthlyIncome[j] += totalAmount;
                foundMonth = 1;
                break;
            }
        }
        if (!foundMonth) {
            strcpy(months[uniqueMonths], month);
            monthlyIncome[uniqueMonths] += totalAmount;
            uniqueMonths++;
        }

        char year[5] = {0};
        strncpy(year, invoices[i].date, 4); // "yyyy"
        int foundYear = 0;
        for (int j = 0; j < uniqueYears; j++) {
            if (strcmp(year, years[j]) == 0) {
                annualIncome[j] += totalAmount;
                foundYear = 1;
                break;
            }
        }
        if (!foundYear) {
            strcpy(years[uniqueYears], year);
            annualIncome[uniqueYears] += totalAmount;
            uniqueYears++;
        }
    }

    printf("Daramad Mahane:\n");
    for (int i = 0; i < uniqueMonths; i++) {
        printf("%s: %d\n", months[i], monthlyIncome[i]);
    }

    printf("Daramad Salane:\n");
    for (int i = 0; i < uniqueYears; i++) {
        printf("%s: %d\n", years[i], annualIncome[i]);
    }
}

void showMenu() {
    printf("Menue:\n");
    printf("1. Darj Faktore Jadid\n");
    printf("2. Darj Mahsol Jadid\n");
    printf("3. Moshahede Faktorehaye yek rooz moshakhas\n");
    printf("4. Moshahede tarikh rooz ba bishtarin moshtari\n");
    printf("5. Moshahede pforush tarin rooz sal\n");
    printf("6. Moshahede gheymat yek mahsol khas\n");
    printf("7. Moshahede daramad salane va mahane\n");
    printf("8. Khorooj\n");
    printf("Lotfan yek gozine ra entekhab konid: ");
}

int main() {
    checkAndCreateFile("products.txt");
    checkAndCreateFile("invoices.txt");

    loadProducts("products.txt");
    loadInvoices("invoices.txt");

    int choice;
    while (1) {
        showMenu();
        scanf("%d", &choice);
        if (choice == 8) {
            break;
        }

        switch (choice) {
            case 1: {
                Invoice newInvoice;
                printf("Shomare Faktor: ");
                scanf("%d", &newInvoice.number);
                printf("Tarikh (yyyy/mm/dd): ");
                scanf("%10s", newInvoice.date);
                printf("Tedad Kala: ");
                scanf("%d", &newInvoice.itemCount);
                for (int i = 0; i < newInvoice.itemCount; i++) {
                    printf("Code Mahsol va Tedad: ");
                    scanf("%d %d", &newInvoice.items[i].code, &newInvoice.items[i].quantity);
                }
                addInvoice(&newInvoice, "invoices.txt");
                break;
            }
            case 2: {
                Product newProduct;
                printf("Code Mahsol: ");
                scanf("%d", &newProduct.code);
                printf("Name Mahsol: ");
                scanf("%49s", newProduct.name);
                printf("Gheymat Mahsol: ");
                scanf("%d", &newProduct.price);
                addProduct(&newProduct, "products.txt");
                break;
            }
            case 3: {
                char date[11];
                printf("Tarikh (yyyy/mm/dd): ");
                scanf("%10s", date);
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
                printf("Code Mahsol: ");
                scanf("%d", &productCode);
                viewProductPrice(productCode);
                break;
            }
            case 7: {
                viewIncome();
                break;
            }
            default: {
                printf("Gozine eshtebah ast. Dobare emtehan konid.\n");
                break;
            }
        }
    }

    return 0;
}
