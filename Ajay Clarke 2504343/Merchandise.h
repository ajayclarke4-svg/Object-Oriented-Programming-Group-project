#ifndef  Merchandise_h
#define  Merchandise_h

class Merchandise {
private:
    string itemType;
    string size;

public:
    Merchandise(){
        itemType = "";
        size = "";
    };
    Merchandise(const string& itemType, const string& size){
        this->itemType = itemType;
        this->size = size;
    };
    Merchandise(const Merchandise& M){
        itemType = M.itemType;
        size = M.size;
    };

    string getItemType();
    string getSize();

    void setItemType(const string& itemType);
    void setSize(const string& size);

    void displayMerchandiseDetails(){
        cout << "Item Type: " << itemType << endl;
        cout << "Size: " << size << endl;
    };
};

#endif // Merchandise_h