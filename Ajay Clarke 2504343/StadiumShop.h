#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Product.h"
#include "Merchandise.h"
#include "FoodItem.h"
using namespace std;

// ============================================================
//  StadiumShop — Manages shop inventory and sales
//  Handles Merchandise and FoodItem products with GCT billing.
// ============================================================
class StadiumShop {
private:
    vector<Product*> inventory;
    double totalRevenue;
    double totalTaxCollected;
    int totalItemsSold;

public:
    // Default constructor
    StadiumShop() {
        this->totalRevenue = 0.0;
        this->totalTaxCollected = 0.0;
        this->totalItemsSold = 0;
    }

    // Destructor — free all dynamically allocated products
    ~StadiumShop() {
        for (int i = 0; i < (int)inventory.size(); i++) {
            delete inventory[i];
        }
        inventory.clear();
    }

    // ---- Getters ----
    double getTotalRevenue() {
        return totalRevenue;
    }
    double getTotalTaxCollected() {
        return totalTaxCollected;
    }
    int getTotalItemsSold() {
        return totalItemsSold;
    }
    vector<Product*>& getInventory() {
        return inventory;
    }

    // ---- Add a product to the shop ----
    void addProduct(Product* p) {
        // Check for duplicate product ID
        for (int i = 0; i < (int)inventory.size(); i++) {
            if (inventory[i]->getProductId() == p->getProductId()) {
                throw DuplicateEntryException("Product ID " + to_string(p->getProductId()) + " already exists in the shop.");
            }
        }
        inventory.push_back(p);
    }

    // ---- Find a product by ID ----
    Product* findProduct(int productId) {
        for (int i = 0; i < (int)inventory.size(); i++) {
            if (inventory[i]->getProductId() == productId) {
                return inventory[i];
            }
        }
        return nullptr;
    }

    // ---- Process a sale ----
    // Returns a formatted receipt string
    // Throws: ProductNotFoundException, InsufficientStockException, InsufficientPaymentException
    string completeSale(int productId, int qty, double payment,
                        double& subtotal, double& tax, double& total, double& change) {
        Product* p = findProduct(productId);
        if (p == nullptr) {
            throw ProductNotFoundException("Product with ID " + to_string(productId) + " not found.");
        }

        // This will throw InsufficientStockException if qty > stock
        p->reduceStock(qty);

        subtotal = p->getPrice() * qty;
        tax = p->calculateTax() * qty;
        total = subtotal + tax;

        if (payment < total) {
            // Undo stock reduction
            p->addStock(qty);
            throw InsufficientPaymentException(
                "Payment of $" + to_string(payment) +
                " is less than total of $" + to_string(total) + ".");
        }

        change = payment - total;
        totalRevenue += total;
        totalTaxCollected += tax;
        totalItemsSold += qty;

        // Build receipt
        stringstream receipt;
        receipt << fixed << setprecision(2);
        receipt << "====== RECEIPT ======" << endl;
        receipt << "Product   : " << p->getName() << endl;
        receipt << "Quantity  : " << qty << endl;
        receipt << "Subtotal  : $" << subtotal << endl;
        receipt << "GCT (15%) : $" << tax << endl;
        receipt << "TOTAL     : $" << total << endl;
        receipt << "Payment   : $" << payment << endl;
        receipt << "Change    : $" << change << endl;
        receipt << "=====================" << endl;
        return receipt.str();
    }

    // ---- Restock a product ----
    void restock(int productId, int qty) {
        Product* p = findProduct(productId);
        if (p == nullptr) {
            throw ProductNotFoundException("Product with ID " + to_string(productId) + " not found.");
        }
        p->addStock(qty);
        cout << "Restocked '" << p->getName() << "' by " << qty << " units. New stock: " << p->getStock() << endl;
    }

    // ---- Display all products ----
    void displayInventory() {
        cout << "======= Stadium Shop Inventory =======" << endl;
        if (inventory.empty()) {
            cout << "No products in inventory." << endl;
            return;
        }
        for (int i = 0; i < (int)inventory.size(); i++) {
            inventory[i]->describe();
            cout << "-------------------------------" << endl;
        }
    }

    // ---- Financial summary ----
    void displayFinancialSummary() {
        cout << "======= Shop Financial Summary =======" << endl;
        cout << fixed << setprecision(2);
        cout << "Total Items Sold      : " << totalItemsSold << endl;
        cout << "Total Revenue         : $" << totalRevenue << endl;
        cout << "Total Tax Collected   : $" << totalTaxCollected << endl;
    }
};

#endif
