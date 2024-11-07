#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Class representing a Product in the store
class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int id, string name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    void display() const {
        cout << setw(5) << id << setw(20) << name
                  << setw(10) << price << setw(10) << stock << endl;
    }
};

// Class representing the Cart containing selected products
class Cart {
private:
    vector<pair<Product, int>> items;

public:
    void addProduct(const Product& product, int quantity) {
        items.push_back({product, quantity});
    }

    void displayCart() const {
        cout << "Your Cart:\n";
        for (const auto& item : items) {
            cout << "Product: " << item.first.name
                      << ", Quantity: " << item.second
                      << ", Total Price: " << item.first.price * item.second << endl;
        }
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.first.price * item.second;
        }
        return total;
    }

    void clear() {
        items.clear();
    }
};

// Class representing a Customer
class Customer {
public:
    string name;
    Cart cart;

    Customer(string name) : name(name) {}

    void viewProducts(const vector<Product>& products) {
        cout << "Available Products:\n";
        for (const auto& product : products) {
            product.display();
        }
    }

    void addToCart(const Product& product, int quantity) {
        cart.addProduct(product, quantity);
    }

    void checkout() {
        cart.displayCart();
        double total = cart.calculateTotal();
        cout << "Total to Pay: $" << total << endl;
        cart.clear();
        cout << "Thank you for your purchase, " << name << "!\n";
    }
};

// Main function to simulate the E-Commerce system
int main() {
    // Sample products
    vector<Product> products = {
        Product(1, "Laptop", 999.99, 10),
        Product(2, "Smartphone", 499.99, 20),
        Product(3, "Headphones", 49.99, 30),
        Product(4, "Keyboard", 19.99, 50)
    };

    // Create a customer
    Customer customer("John Doe");

    int choice;
    while (true) {
        cout << "\n--- E-Commerce System ---\n";
        cout << "1. View Products\n2. Add to Cart\n3. View Cart\n4. Checkout\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            customer.viewProducts(products);
        } else if (choice == 2) {
            int productId, quantity;
            cout << "Enter Product ID to add to cart: ";
            cin >> productId;
            cout << "Enter Quantity: ";
            cin >> quantity;

            if (productId > 0 && productId <= products.size() && quantity <= products[productId - 1].stock) {
                customer.addToCart(products[productId - 1], quantity);
                cout << "Added to cart!\n";
            } else {
                cout << "Invalid product ID or insufficient stock.\n";
            }
        } else if (choice == 3) {
            customer.cart.displayCart();
        } else if (choice == 4) {
            customer.checkout();
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
