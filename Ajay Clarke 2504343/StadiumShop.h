#ifndef STADIUMSHOP_H
#define STADIUMSHOP_H

#include <string>
#include <vector>
#include "Product.h"
#include "Merchandise.h"
#include "Fooditem.h"
 using namespace std;

 

class StadiumShop {
private:
    vector<Product*> inventory;
    double totalRevenue;
    double totalTaxCollected;
    int totalItemsSold;
public:
    static constexpr double SHOP_GCT_RATE = 0.15; // 15% GCT
    StadiumShop(){
        totalRevenue = 0.0;
        totalTaxCollected = 0.0;
        totalItemsSold = 0;
    };
    
    ~StadiumShop();

    // Prevent accidental shallow copies
    StadiumShop(const StadiumShop&) = delete;
    StadiumShop& operator=(const StadiumShop&) = delete;

    // Inventory operations
    void addProduct(Product* product);
    bool removeProduct(int productId);

    Product* findProduct(int productId);
    const Product* findProduct(int productId) const;

    void restock(int productId, int quantity);
    void displayInventory() const;
    
    const vector<Product*>& getInventory() const;
    void clearInventory();

    // Sales transactions
    // Calculates subtotal, tax, total payment, and change; throws InsufficientPaymentException or NegativeValueException
    string completeSale(int productId, int quantity, double paymentAmount,
                             double& outSubtotal, double& outTax, double& outTotal, double& outChange);

    // Financial reporting
    double getTotalRevenue() const;
    double getTotalTaxCollected() const;
    int getTotalItemsSold() const;
    void setFinancials(double revenue, double tax, int itemsSold);
    void displayFinancialSummary() const;
};

#endif // STADIUMSHOP_H
