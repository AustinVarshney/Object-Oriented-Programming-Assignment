#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User
{
public:
    int userId;
    string name, email, password, address, phone, userType;

    User(int uid, string n, string em, string pw, string addr, string ph, string type)
        : userId(uid), name(n), email(em), password(pw), address(addr), phone(ph), userType(type) {}

    virtual void displayUserInfo()
    {
        cout << "User ID: " << userId << "\nName: " << name << "\nEmail: " << email << endl;
    }

    virtual void viewDashboard() = 0; // To be implemented by derived classes
};

class Customer : public User
{
public:
    Customer(int uid, string n, string em, string pw, string addr, string ph)
        : User(uid, n, em, pw, addr, ph, "Customer") {}

    void viewDashboard() override
    {
        cout << "Customer Dashboard\n";
        // Additional customer-specific options
    }
};

class Seller : public User
{
public:
    Seller(int uid, string n, string em, string pw, string addr, string ph)
        : User(uid, n, em, pw, addr, ph, "Seller") {}

    void viewDashboard() override
    {
        cout << "Seller Dashboard\n";
        // Additional seller-specific options
    }
};

class Admin : public User
{
public:
    Admin(int uid, string n, string em, string pw, string addr, string ph)
        : User(uid, n, em, pw, addr, ph, "Admin") {}

    void viewDashboard() override
    {
        cout << "Admin Dashboard\n";
        // Additional admin-specific options
    }
};

class Product
{
public:
    int productId, stock;
    double price;
    string name, description, category;
    int sellerId;

    Product(int pid, string n, string desc, double pr, int st, string cat, int sid)
        : productId(pid), name(n), description(desc), price(pr), stock(st), category(cat), sellerId(sid) {}

    void displayProduct()
    {
        cout << "Product ID: " << productId << "\nName: " << name << "\nPrice: $" << price
             << "\nStock: " << stock << "\nCategory: " << category << endl;
    }

    void updateStock(int amount) { stock += amount; }
    void updatePrice(double newPrice) { price = newPrice; }
};

class OrderItem
{
private:
    int productId, quantity;
    double price;

public:
    OrderItem(int pid, int qty, double pr) : productId(pid), quantity(qty), price(pr) {}

    double calculateSubtotal() { return quantity * price; }

    void displayOrderItem()
    {
        cout << "Product ID: " << productId << ", Quantity: " << quantity
             << ", Price per unit: $" << price << ", Subtotal: $" << calculateSubtotal() << endl;
    }
};

class Order
{
private:
    int orderId, userId;
    string status;
    vector<OrderItem> items;
    double totalAmount;

public:
    Order(int oid, int uid) : orderId(oid), userId(uid), status("Pending"), totalAmount(0.0) {}

    void addItem(OrderItem item)
    {
        items.push_back(item);
        totalAmount += item.calculateSubtotal();
    }

    void calculateTotal()
    {
        totalAmount = 0;
        for (const auto &item : items)
        {
            totalAmount += item.calculateSubtotal();
        }
    }

    void updateStatus(string newStatus) { status = newStatus; }

    void displayOrder()
    {
        cout << "Order ID: " << orderId << "\nStatus: " << status << "\nTotal Amount: $" << totalAmount << endl;
        for (const auto &item : items){
            item.displayOrderItem();
        }
    }
};

class Review
{
private:
    int reviewId, productId, userId, rating;
    string comment;

public:
    Review(int rid, int pid, int uid, int rate, string com)
        : reviewId(rid), productId(pid), userId(uid), rating(rate), comment(com) {}

    void displayReview()
    {
        cout << "Review ID: " << reviewId << "\nProduct ID: " << productId
             << "\nRating: " << rating << "\nComment: " << comment << endl;
    }
};

int main()
{
    // Create some users
    Customer customer1(1, "John Doe", "john@example.com", "password123", "123 Main St", "123-456-7890");
    Seller seller1(2, "Alice Smith", "alice@example.com", "pass456", "456 Market St", "098-765-4321");
    Admin admin1(3, "Admin User", "admin@example.com", "adminpass", "Admin St", "112-233-4455");

    // Display user info and dashboard
    customer1.displayUserInfo();
    customer1.viewDashboard();

    // Create a product
    Product product1(101, "Laptop", "High-performance laptop", 999.99, 10, "Electronics", seller1.userId);
    product1.displayProduct();

    // Create an order and add items
    Order order1(1001, customer1.userId);
    OrderItem item1(101, 2, 999.99);
    order1.addItem(item1);
    order1.calculateTotal();
    order1.updateStatus("Shipped");
    order1.displayOrder();

    // Add a review
    Review review1(201, product1.productId, customer1.userId, 5, "Excellent product!");
    review1.displayReview();

    return 0;
}
