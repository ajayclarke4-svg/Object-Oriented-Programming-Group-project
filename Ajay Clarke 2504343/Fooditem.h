#ifndef Fooditem_H
#define Fooditem_H

#include <iostream>

class Fooditem {
private:
   bool isBeverage;

public:
    Fooditem(){
        isBeverage = false;
    };
    Fooditem(bool isBeverage){
        this->isBeverage = isBeverage;
    };
    Fooditem(const Fooditem& F){
        isBeverage = F.isBeverage;
    };

    void describe() {
        cout << "This is a food item." << endl;
    }

};

#endif // Fooditem_H