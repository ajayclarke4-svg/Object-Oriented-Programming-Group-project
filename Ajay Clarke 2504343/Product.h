#ifndef PRODUCT_H
#define PRODUCT_H

class Product {
private:
    int productId;
    string name;
    double price;
    int stock;

public:
    Product(){
        productId = 0;
        name = "";
        price = 0.0;
        stock = 0;
    };

    Product(int id, const string& name, double price, int stock){
        this->productId = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    };

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

    void setProductId(int id);
    void setName(const string& name);
    void setPrice(double price);
    void setStock(int stock);

    void describe(){
        cout << "Product ID: " << productId << endl;
        cout << "Name: " << name << endl;
        cout << "Price: $" << price << endl;
        cout << "Stock: " << stock << endl;
    };
};

#endif // PRODUCT_H