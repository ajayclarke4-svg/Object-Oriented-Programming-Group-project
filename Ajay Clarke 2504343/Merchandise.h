#ifndef MERCHANDISE_H
#define MERCHANDISE_H

#include "Product.h"
#include <string>
using namespace std;

class Merchandise : public Product {
private:
    string itemType;
    string size;
public:
    //Default Constructor
    Merchandise(){
        itemType = "Jersey";
        size = "Standard";
    };
    //Primary Constructor 
    Merchandise(int id, string name, double price, int stock, string type, string itemSize)
                :Product(id, name, price, stock){
        itemType = type;
        size = itemSize;
    };
    //Copy Construtor
    Merchandise(const Merchandise& other)
                :Product(other){
        itemType = other.itemType;
        size = other.size;
    };
    
    // Accessors
    string getItemType(){
        return itemType;
    };
    string getSize(){
        return size;
    };

    // Mutators with validation
    void setItemType(string type){
        if (type.empty()) {
            throw InvalidDataException("Merchandise item type cannot be empty.");
        }
        itemType = type;
    };
    void setSize(string itemSize){
        if (itemSize.empty()) {
            throw InvalidDataException("Merchandise size cannot be empty.");
        }
        size = itemSize;
    };

    // Polymorphic methods
    virtual void describe()override{
        cout << "[Merchandise] ID: " << productId
              << " | Name: " << name
              << " | Type: " << itemType
              << " | Size: " << size
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " (excl. 15% GCT: $" << calculateTax() << ")"
              << " | Stock: " << stock << std::endl;
    };

    // Storable interface methods
    virtual string toRecord() override{
        vector<string> fields;
        fields.push_back("Merchandise");
        fields.push_back(FileManager::toText(productId));
        fields.push_back(name);
        fields.push_back(FileManager::toText(price));
        fields.push_back(FileManager::toText(stock));
        fields.push_back(itemType);
        fields.push_back(size);
        return FileManager::joinFields(fields);
    };
    virtual void fromRecord() override{
        string record;
        vector<string> fields = FileManager::splitFields(record);
        if (fields.size() < 7) {
            throw InvalidDataException("Merchandise record requires 7 fields: " + record);
        }
        setProductId(FileManager::toInt(fields[1]));
        setName(fields[2]);
        setPrice(FileManager::toDouble(fields[3]));
        setStock(FileManager::toInt(fields[4]));
        setItemType(fields[5]);
        setSize(fields[6]);
        };
};

#endif // MERCHANDISE_H
