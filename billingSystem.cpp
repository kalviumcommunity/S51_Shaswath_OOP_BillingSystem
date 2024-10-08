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
    static int itemCount;  // Static variable to keep track of the number of items

public:
    Item(int id = 0, string name = "", double price = 0.0, double discount = 0.0)
        : itemId(id), itemName(name), price(price), discount(discount) {
        itemCount++;
    }

    static int getItemCount() {
        return itemCount;
    }

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

// Initialize the static variable
int Item::itemCount = 0;

// Customer class definition
class Customer {
private:
    string name;
    string phoneNumber;
    static int customerCount;  // Static variable to keep track of the number of customers

public:
    Customer(string name = "", string phoneNumber = "")
        : name(name), phoneNumber(phoneNumber) {
        customerCount++;
    }

    static int getCustomerCount() {
        return customerCount;
    }

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

// Initialize the static variable
int Customer::customerCount = 0;

// Base Billing class definition (Abstract Class)
class Billing {
protected:
    vector<Item> items;
    Customer* customer;

public:
    Billing(Customer* customer) : customer(customer) {}

    virtual ~Billing() {
        delete customer;
    }

    void addItem(const Item& item) {
        items.push_back(item);
    }

    void displayItems() const {
        cout << "Items List:" << endl;
        for (const auto& item : items) {
            item.display();
        }
    }

    virtual double calculateTotal() const = 0;  // Pure virtual function

    void generateInvoice() const {
        cout << "Invoice:" << endl;
        customer->display();
        displayItems();
        cout << "Total Amount: $" << fixed << setprecision(2) << calculateTotal() << endl;
        cout << "Total Items Added: " << Item::getItemCount() << endl;
        cout << "Total Customers Served: " << Customer::getCustomerCount() << endl;
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

// Derived RegularBilling class definition
class RegularBilling : public Billing {
public:
    RegularBilling(Customer* customer) : Billing(customer) {}

    double calculateTotal() const override {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getDiscountedPrice();
        }
        return total;
    }
};

// Class Discount Policy
class DiscountPolicy {
protected:
    double additionalDiscount;

public:
    DiscountPolicy(double discount = 0.0) : additionalDiscount(discount) {}

    
    double applyAdditionalDiscount(double total) const {
        return total - additionalDiscount;
    }
};


// Derived DiscountedBilling class definition
class DiscountedBilling : public Billing, public DiscountPolicy {
public:
    DiscountedBilling(Customer* customer, double discount)
        : Billing(customer), DiscountPolicy(discount) {}

    double calculateTotal() const override {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getDiscountedPrice();
        }
        return applyAdditionalDiscount(total); 
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

    cout << "Enter customer name: ";
    getline(cin, customerName);
    cout << "Enter customer phone number: ";
    getline(cin, customerPhone);

    // Create a customer and billing instance dynamically
    Customer* customer = new Customer(customerName, customerPhone);
    Billing* billing = nullptr;

    cout << "Choose billing type:\n";
    cout << "1. Regular Billing\n";
    cout << "2. Discounted Billing\n";
    cout << "Enter your choice: ";
    int billingChoice;
    cin >> billingChoice;

    if (billingChoice == 1) {
        billing = new RegularBilling(customer);
    } else if (billingChoice == 2) {
        double additionalDiscount;
        cout << "Enter additional discount amount: ";
        cin >> additionalDiscount;
        billing = new DiscountedBilling(customer, additionalDiscount);
    } else {
        cout << "Invalid choice!" << endl;
        delete customer;
        return 1;
    }

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
                editItem(*billing);
                break;
            case 3:
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
