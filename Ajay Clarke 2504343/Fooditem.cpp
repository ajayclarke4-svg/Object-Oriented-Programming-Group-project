#include "Fooditem.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
using namespace std;

FoodItem::FoodItem(): 
    Product(0, "Match Snack", 0.0, 0), isBeverage(false), portionSize("Regular") {}

FoodItem::FoodItem(int id, const string& name, double price, int stock, bool beverage, const string& portion) 
                :Product(id, name, price, stock) {
    setIsBeverage(beverage);
    setPortionSize(portion);
}
FoodItem::FoodItem(const FoodItem& other) 
                : Product(other.productId, other.name, other.price, other.stock),
                        isBeverage(other.isBeverage), portionSize(other.portionSize) {}
             
bool FoodItem::getIsBeverage() {
    return isBeverage;
}
string FoodItem::getPortionSize() {
    return portionSize;
}
void FoodItem::setIsBeverage(bool beverage) {
    isBeverage = beverage;
}
void FoodItem::setPortionSize(const string& portion) {
    if (portion.empty()) {
        throw InvalidDataException("Food item portion size cannot be empty.");
    }
    portionSize = portion;
}
void FoodItem::describe() const {
    cout << "[Food/Drink] ID: " << productId
              << " | Name: " << name
              << " | Type: " << (isBeverage ? "Beverage" : "Food")
              << " | Portion: " << portionSize
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " (excl. 15% GCT: $" << calculateTax() << ")"
              << " | Stock: " << stock << std::endl;
}
string FoodItem::getProductType() const {
    return isBeverage ? "Beverage" : "Food";
}
string FoodItem::toRecord() const {
    vector<string> fields;
    fields.push_back("FoodItem");
    fields.push_back(FileManager::toText(productId));
    fields.push_back(name);
    fields.push_back(FileManager::toText(price));
    fields.push_back(FileManager::toText(stock));
    fields.push_back(isBeverage ? "1" : "0");
    fields.push_back(portionSize);
    return FileManager::joinFields(fields);
}
void FoodItem::fromRecord(const string& record) {
    vector<string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("FoodItem record requires 7 fields: " + record);
    }
    setProductId(FileManager::toInt(fields[1]));
    setName(fields[2]);
    setPrice(FileManager::toDouble(fields[3]));
    setStock(FileManager::toInt(fields[4]));
    setIsBeverage(fields[5] == "1" || fields[5] == "true");
    setPortionSize(fields[6]);
}
