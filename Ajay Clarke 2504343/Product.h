#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include "Storable.h"
#include "FileManager.h"
using namespace std;

// Abstract superclass for all items sold in the stadium shop
class Product : public Storable {
protected:
    int productId;
    string name;
    double price;
    int stock;
public:
    static const double GCT_RATE = 0.15; //General Consumption Tax
    //Default Constructor
    Product(){
        productId = 0;
        name = "Unknown";
        price = 0.0;
        stock = 0;
    };
    //Primary Constructor 
    Product(int id, const string& productName, double productPrice, int initialStock){
        this->productId = id;
        this->name = productName;
        this->price = productPrice;
        this->stock = initialStock;
    };
    //Destructor
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
        if (id <= 0) {
            throw InvalidDataException("Product ID cannot be negativem or zero.");
        }
        this->productId = id;
    };
    void setName(string Name){
        if (Name.empty()) {
            throw InvalidDataException("Product name cannot be empty.");
        }
        this->name = Name;
    };
    void setPrice(double Price){
        if (Price <= 0) {
            throw InvalidDataException("Product price cannot be negative or free.");
        }
        this->price = Price;
    };
    void setStock(int Stock){
        if (Stock < 0) {
            throw InvalidDataException("Product stock cannot be negative.");
        }
        this->stock = Stock;
    };

    void addStock(int quantity){
        if (quantity <= 0) {
            throw InvalidDataException("Quantity to add must be positive number.");
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
        else{
            this->stock -= quantity;
        }
    };

    // Tax calculation
    virtual double calculateTax(int quantity = 1){
         return (price * quantity) * GCT_RATE;
    };
    virtual double calculateTotal(int quantity = 1){
        double subtotal = price * quantity;
        return subtotal + calculateTax(quantity);
    };

    virtual string getProductType() const {
        return "Product";
    };

    // Pure virtual methods
    virtual void describe() = 0;

    // Write to file 
    string Product::toRecord() const {
        vector<string> fields;

        fields.push_back(getProductType());
        fields.push_back(FileManager::toText(productId));
        fields.push_back(name);
        fields.push_back(FileManager::toText(price));
        fields.push_back(FileManager::toText(stock));

        return FileManager::joinFields(fields);
    }

    // Read to file
    void Product::fromRecord(const string& record) {
        vector<string> fields = FileManager::splitFields(record);

        if (fields.size() < 5) {
            throw InvalidDataException("Product record requires at least 5 fields: " + record);
        }

        setProductId(FileManager::toInt(fields[1]));
        setName(fields[2]);
        setPrice(FileManager::toDouble(fields[3]));
        setStock(FileManager::toInt(fields[4]));
    }
};

#endif // PRODUCT_H
