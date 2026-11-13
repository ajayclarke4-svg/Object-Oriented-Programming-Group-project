#ifndef TICKET_H
#define TICKET_H

class Ticket {
private:
    int ticketId;
    string category;
    double price;

public:
    Ticket(){
        ticketId = 0;
        category = "";
        price = 0.0;
    };

    Ticket(int id, const string& category, double price){
        this->ticketId = id;
        this->category = category;
        this->price = price;
    };
    
    Ticket(const Ticket &T){
        this->ticketId = T.ticketId;
        this->category = T.category;
        this->price = T.price;
    };

    int getTicketId(){
        return ticketId;
    };
    string getCategory(){
        return category;
    };
    double getPrice(){
        return price;
    };

    int setTicketId(int id);
    string setCategory(const string& category);
    double setPrice(double price);

    void displayTicketDetails(){
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Category: " << category << endl;
        cout << "Price: $" << price << endl;
    };
};

#endif // TICKET_H