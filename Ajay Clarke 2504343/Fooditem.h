#ifndef FOODITEM_H
#define FOODITEM_H

#include "Product.h"
#include "Storable.h"
#include "Exceptions.h"
#include <string>
using namespace std;

class FoodItem : public Product {
private:
    bool isBeverage;
    string portionSize;
public:
    //Default Constructor
    FoodItem(){
        isBeverage = false;
        portionSize = "Regular";
    };
    //Primary Constructor
    FoodItem(int id, string name, double price, int stock, bool beverage, string portion = "Regular"):Product(id, name, price, stock){
        isBeverage = beverage;
        portionSize = portion;
    };
    //Copy Constructor
    FoodItem(const FoodItem& other):Product(other){
        isBeverage = other.isBeverage;
        portionSize = other.portionSize;
    };

    // Accessors
    bool getIsBeverage(){
        return isBeverage;
    };
    string getPortionSize(){
        return portionSize;
    };

    // Mutators with validation
    void setIsBeverage(bool beverage){
        this->isBeverage = beverage;
    };
    void setPortionSize(string portion){
        if (portion.empty()) {
            throw InvalidDataException("Food item portion size cannot be empty.");
        }
        this->portionSize = portion;
    };
    
    // Polymorphic methods
    virtual void describe() override{
        cout << "[Food/Drink] ID: " << productId
              << " | Name: " << name
              << " | Type: " << (isBeverage ? "Beverage" : "Food")
              << " | Portion: " << portionSize
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " (excl. 15% GCT: $" << calculateTax() << ")"
              << " | Stock: " << stock << std::endl;
    };

    // Storable interface methods
    virtual string toRecord() override{
        vector<string> fields;
        fields.push_back("FoodItem");
        fields.push_back(FileManager::toText(productId));
        fields.push_back(name);
        fields.push_back(FileManager::toText(price));
        fields.push_back(FileManager::toText(stock));
        fields.push_back(isBeverage ? "1" : "0");
        fields.push_back(portionSize);
        return FileManager::joinFields(fields);
    };

    virtual void fromRecord() override{
        string record;
        vector<string> fields = FileManager::splitFields(record);
        
        if (fields.size() < 7) {
        throw InvalidDataException("FoodItem record requires 7 fields: " + record);
        }

        setProductId(FileManager::toInt(fields[1]));
        setName(fields[2]);
        setPrice(FileManager::toDouble(fields[3]));
        setStock(FileManager::toInt(fields[4]));
        setIsBeverage(fields[5] == "1" || fields[5] == "true");
        setPortionSize(fields[6]);
    };
};

#endif // FOODITEM_H
