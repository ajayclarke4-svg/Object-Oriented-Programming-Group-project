#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include "Storable.h"
using namespace std;

// Abstract superclass for all items sold in the stadium shop
class Product : public Storable {
protected:
    int productId;
    string name;
    double price;
    int stock;
public:
    static constexpr double GCT_RATE = 0.15; // 15% General Consumption Tax
    Product(){
        productId = 0;
        name = "Unknown";
        price = 0.0;
        stock = 0;
    };
    Product(int id, const string& productName, double productPrice, int initialStock){
        this->productId = id;
        this->name = productName;
        this->price = productPrice;
        this->stock = initialStock;
    };
    
    virtual ~Product(){}

    // Accessors
    int getProductId(){
        return productId;
    };
    string getName(){
        return name;
    };
    double getPrice(){
        return price;
    };
    int getStock(){
        return stock;
    };

    // Mutators with validation
    void setProductId(int id){
        if (id < 0) {
            throw InvalidDataException("Product ID cannot be negative.");
        }
        this->productId = id;
    };
    void setName(const string& newName){
        if (newName.empty()) {
            throw InvalidDataException("Product name cannot be empty.");
        }
        this->name = newName;
    };
    void setPrice(double newPrice){
        if (newPrice < 0) {
            throw InvalidDataException("Product price cannot be negative.");
        }
        this->price = newPrice;
    };
    void setStock(int newStock){
        if (newStock < 0) {
            throw InvalidDataException("Product stock cannot be negative.");
        }
        this->stock = newStock;
    };
    void addStock(int quantity){
        if (quantity <= 0) {
            throw InvalidDataException("Quantity to add must be positive.");
        }
        this->stock += quantity;
    };
    void reduceStock(int quantity){
        if (quantity <= 0) {
            throw InvalidDataException("Quantity to reduce must be positive.");
        }
        if (quantity > this->stock) {
            throw InvalidDataException("Not enough stock to reduce.");
        }
        this->stock -= quantity;
    };

    // Tax calculation
    virtual double calculateTax(int quantity = 1) const;
    virtual double calculateTotal(int quantity = 1) const;

    // Pure virtual methods
    virtual void describe() const = 0;
    virtual string getProductType() const = 0;

    // Storable interface methods
    virtual string toRecord() const override;
    virtual void fromRecord(const string& record) override;
};

#endif // PRODUCT_H
