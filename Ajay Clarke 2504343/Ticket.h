#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "Storable.h"
class Ticket : public Storable {
private:
    int ticketId;
    int fixtureId;
    string category; 
    double price;
    bool isSold;
    int spectatorId;

public:
    static const double TICKET_GCT_RATE = 0.15; // GCT
    Ticket(){
        ticketId = 0;
        fixtureId = 0;
        category = "General";
        price = 0.0;
        isSold = false;
        spectatorId = 0;
    };
    Ticket(int id, int fixId, const std::string& cat, double ticketPrice, bool sold = false, int specId = 0){
        this->ticketId = id;
        this->fixtureId = fixId;
        this->category = cat;
        this->price = ticketPrice;
        this->isSold = sold;
        this->spectatorId = specId;
    };
    Ticket(const Ticket& other){
        this->ticketId = other.ticketId;
        this->fixtureId = other.fixtureId;
        this->category = other.category;
        this->price = other.price;
        this->isSold = other.isSold;
        this->spectatorId = other.spectatorId;
    };

    // Accessors
    int getTicketId() const{
        return ticketId;
    };
    int getFixtureId() const{
        return fixtureId;
    };
    string getCategory() const{
        return category;
    };
    double getPrice() const{
        return price;
    };
    bool getIsSold() const{
        return isSold;
    };
    int getSpectatorId() const{
        return spectatorId;
    };

    double calculateTax() const{
        return price * TICKET_GCT_RATE;
    };
    double calculateTotalPrice() const{
        return price + calculateTax();
    };

    // Mutators with validation
    void setTicketId(int id){
        if (id < 0) {
            throw InvalidDataException("Ticket ID cannot be negative.");
        }
        this->ticketId = id;
    };
    void setFixtureId(int fixId){
        if (fixId < 0) {
            throw InvalidDataException("Fixture ID cannot be negative.");
        }
        this->fixtureId = fixId;
    };
    void setCategory(string& cat){
        if (cat.empty()) {
            throw InvalidDataException("Category cannot be empty.");
        }
        this->category = cat;
    };
    void setPrice(double ticketPrice){
        if (ticketPrice < 0) {
            throw InvalidDataException("Ticket price cannot be negative.");
        }
        this->price = ticketPrice;
    };
    void markAsSold(int specId){
        if (specId < 0) {
            throw InvalidDataException("Spectator ID cannot be negative.");
        }
        this->isSold = true;
        this->spectatorId = specId;
    };
    void resetSold(){
        this->isSold = false;
        this->spectatorId = 0;
    };

    // Display
    void displayTicketDetails() {
        cout << "Ticket ID: " << ticketId << "\n";
        cout << "Fixture ID: " << fixtureId << "\n";
        cout << "Category: " << category << "\n";
        cout << "Price: $" << price << "\n";
        cout << "Tax: $" << calculateTax() << "\n";
        cout << "Total Price: $" << calculateTotalPrice() << "\n";
        cout << "Sold: " << (isSold ? "Yes" : "No") << "\n";
        if (isSold) {
            cout << "Spectator ID: " << spectatorId << "\n";
        }
    };

    // Storable interface methods
    virtual string toRecord() const override;
    virtual void fromRecord(const string& record) override;
};

#endif // TICKET_H
