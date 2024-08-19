#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Item class definition
class Item {
private:
    int itemId;
    string itemName;
    double price;
    double discount;

public:
    Item(int id = 0, string name = "", double price = 0.0, double discount = 0.0)
        : itemId(id), itemName(name), price(price), discount(discount) {}

    void display() const {
        cout << "Item ID: " << itemId
             << ", Name: " << itemName
             << ", Price: $" << price
             << ", Discount: $" << discount << endl;
    }

    double getDiscountedPrice() const {
        return price - discount;
    }

    // Getter and Setter methods
    int getId() const { return itemId; }
    string getName() const { return itemName; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }

    Item& setName(const string& newName) { 
        itemName = newName; 
        return *this; 
    }

    Item& setPrice(double newPrice) { 
        price = newPrice; 
        return *this; 
    }

    Item& setDiscount(double newDiscount) { 
        discount = newDiscount; 
        return *this; 
    }
};

// Customer class definition
class Customer {
private:
    string name;
    string phoneNumber;

public:
    Customer(string name = "", string phoneNumber = "")
        : name(name), phoneNumber(phoneNumber) {}

    void display() const {
        cout << "Customer Name: " << name
             << ", Phone Number: " << phoneNumber << endl;
    }

    // Getter and Setter methods
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }

    Customer& setName(const string& newName) {
        name = newName;
        return *this;
    }

    Customer& setPhoneNumber(const string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
        return *this;
    }
};

// Billing class definition
class Billing {
private:
    vector<Item> items;  // Vector of Item objects
    Customer* customer;  // Pointer to Customer object

public:
    Billing(Customer* customer) : customer(customer) {}

    ~Billing() {
        delete customer;  // Deleting the dynamically allocated Customer object
    }

    void addItem(const Item& item) {
        items.push_back(item);  // Adding item to vector
    }

    void displayItems() const {
        cout << "Items List:" << endl;
        for (const auto& item : items) {
            item.display();
        }
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getDiscountedPrice();
        }
        return total;
    }

    void generateInvoice() const {
        cout << "Invoice:" << endl;
        customer->display();
        displayItems();
        cout << "Total Amount: $" << fixed << setprecision(2) << calculateTotal() << endl;
    }

    bool editItem(int id, const string& newName, double newPrice, double newDiscount) {
        for (auto& item : items) {
            if (item.getId() == id) {
                item.setName(newName)
                      .setPrice(newPrice)
                      .setDiscount(newDiscount);
                return true;
            }
        }
        return false;
    }
};

// Function to add an item dynamically
void addItem(Billing& billing) {
    int id;
    string name;
    double price, discount;

    cout << "Enter item ID: ";
    cin >> id;
    cin.ignore(); // To ignore leftover newline character
    cout << "Enter item name: ";
    getline(cin, name);
    cout << "Enter item price: ";
    cin >> price;
    cout << "Enter item discount: ";
    cin >> discount;

    billing.addItem(Item(id, name, price, discount));
}

// Function to edit an item dynamically
void editItem(Billing& billing) {
    int id;
    cout << "Enter item ID to edit: ";
    cin >> id;
    cin.ignore(); // To ignore leftover newline character

    string newName;
    double newPrice, newDiscount;

    cout << "Enter new name: ";
    getline(cin, newName);
    cout << "Enter new price: ";
    cin >> newPrice;
    cout << "Enter new discount: ";
    cin >> newDiscount;

    if (billing.editItem(id, newName, newPrice, newDiscount)) {
        cout << "Item updated successfully." << endl;
    } else {
        cout << "Item not found." << endl;
    }
}

int main() {
    string customerName, customerPhone;
    int choice;

    // Get customer details
    cout << "Enter customer name: ";
    getline(cin, customerName);
    cout << "Enter customer phone number: ";
    getline(cin, customerPhone);

    // Create a customer and billing instance dynamically
    Customer* customer = new Customer(customerName, customerPhone);
    Billing* billing = new Billing(customer);

    do {
        cout << "\nMenu:\n";
        cout << "1. Add item\n";
        cout << "2. Edit item\n";
        cout << "3. Generate invoice\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore leftover newline character

        switch (choice) {
            case 1:
                // Add items dynamically
                int numItems;
                cout << "Enter number of items: ";
                cin >> numItems;
                cin.ignore(); // To ignore leftover newline character

                for (int i = 0; i < numItems; ++i) {
                    cout << "Enter details for item " << (i + 1) << ":" << endl;
                    addItem(*billing);
                }
                break;
            case 2:
                // Edit an item
                editItem(*billing);
                break;
            case 3:
                // Generate and display the invoice
                billing->generateInvoice();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    // Delete the dynamically allocated billing object
    delete billing;

    return 0;
}
