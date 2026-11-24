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
    Merchandise(){
        itemType = "Jersey";
        size = "Standard";
    };
    Merchandise(int id, const string& name, double price, int stock, const string& type, const string& itemSize)
                :Product(id, name, price, stock){
        itemType = type;
        size = itemSize;
    };
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
    void setItemType(const string& type){
        if (type.empty()) {
            throw InvalidDataException("Merchandise item type cannot be empty.");
        }
        itemType = type;
    };
    void setSize(const string& itemSize){
        if (itemSize.empty()) {
            throw InvalidDataException("Merchandise size cannot be empty.");
        }
        size = itemSize;
    };

    // Polymorphic methods
    virtual void describe() const override;
    virtual string getProductType() const override;

    // Storable interface methods
    virtual string toRecord() const override;
    virtual void fromRecord(const string& record) override;
};

#endif // MERCHANDISE_H
