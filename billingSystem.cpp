#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    int id;
    string name;

public:
    Item(int id, string name) : id(id), name(name) {}

    void display() const {
        cout << "Item ID: " << id << ", Name: " << name << endl;
    }

    int getId() const {
        return id;
    }
};

class Customer {
private:
    string name;
    string phoneNumber;

public:
    Customer(string name, string phoneNumber) : name(name), phoneNumber(phoneNumber) {}

    void display() const {
        cout << "Customer Name: " << name << ", Phone Number: " << phoneNumber << endl;
    }

    string getName() const {
        return name;
    }
};

int main() {
    Item item1(101, "Laptop");
    Customer customer1("Alice", "123-456-7890");

    item1.display();
    customer1.display();

    cout << "Item ID from getter function: " << item1.getId() << endl;
    cout << "Customer Name from getter function: " << customer1.getName() << endl;

    return 0;
}
