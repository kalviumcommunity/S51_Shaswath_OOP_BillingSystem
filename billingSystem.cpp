#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Item class definition
class Item
{
private:
    int itemId;
    string itemName;
    double price;
    double discount;

public:
    Item(int id, string name, double price, double discount = 0.0)
        : itemId(id), itemName(name), price(price), discount(discount) {}

    void display() const
    {
        cout << "Item ID: " << itemId
             << ", Name: " << itemName
             << ", Price: $" << price
             << ", Discount: $" << discount << endl;
    }

    double getDiscountedPrice() const
    {
        return price - discount;
    }

    // Getter and Setter methods
    int getId() const { return itemId; }
    string getName() const { return itemName; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }

    Item &setName(const string &newName)
    {
        this->itemName = newName;
        return *this;
    }

    Item &setPrice(double newPrice)
    {
        this->price = newPrice;
        return *this;
    }

    Item &setDiscount(double newDiscount)
    {
        this->discount = newDiscount;
        return *this;
    }
};

// Customer class definition
class Customer
{
private:
    string name;
    string phoneNumber;

public:
    Customer(string name = "", string phoneNumber = "")
        : name(name), phoneNumber(phoneNumber) {}

    void display() const
    {
        cout << "Customer Name: " << name
             << ", Phone Number: " << phoneNumber << endl;
    }

    // Getter and Setter methods
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }

    Customer &setName(const string &newName)
    {
        this->name = newName;
        return *this;
    }

    Customer &setPhoneNumber(const string &newPhoneNumber)
    {
        this->phoneNumber = newPhoneNumber;
        return *this;
    }
};

// Billing class definition
class Billing
{
private:
    vector<Item> items;
    Customer customer;

public:
    Billing(Customer customer) : customer(customer) {}

    Billing &addItem(const Item &item)
    {
        this->items.push_back(item);
        return *this;
    }

    void displayItems() const
    {
        cout << "Items List:" << endl;
        for (const auto &item : items)
        {
            item.display();
        }
    }

    double calculateTotal() const
    {
        double total = 0.0;
        for (const auto &item : items)
        {
            total += item.getDiscountedPrice();
        }
        return total;
    }

    void generateInvoice() const
    {
        cout << "Invoice:" << endl;
        customer.display();
        displayItems();
        cout << "Total Amount: $" << fixed << setprecision(2) << calculateTotal() << endl;
    }

    vector<Item> &getItems() { return items; }
};

// Function to add an item dynamically
void addItem(Billing &billing)
{
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

int main()
{
    string customerName, customerPhone;
    int choice;

    // Get customer details
    cout << "Enter customer name: ";
    getline(cin, customerName);
    cout << "Enter customer phone number: ";
    getline(cin, customerPhone);

    // Create a customer and billing instance
    Customer customer(customerName, customerPhone);
    Billing billing(customer);

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add item\n";
        cout << "2. Generate invoice\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore leftover newline character

        switch (choice)
        {
        case 1:
            // Add items dynamically
            int numItems;
            cout << "Enter number of items: ";
            cin >> numItems;
            cin.ignore(); // To ignore leftover newline character

            for (int i = 0; i < numItems; ++i)
            {
                cout << "Enter details for item " << (i + 1) << ":" << endl;
                addItem(billing);
            }
            break;
        case 2:
            // Generate and display the invoice
            billing.generateInvoice();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 3);

    return 0;
}
