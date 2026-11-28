#pragma once
#include "Person.h"

//Spectator Header File
#ifndef SPECTATOR_H
#define SPECTATOR_H

// Step 1: the Spectator's own data only. Inheritance from Person comes next.
class Spectator : public Person{
private:
    int ticketsBought;
public:
    Spectator(){
        ticketsBought = 0;
    };
    Spectator(int tickets){
        this-> ticketsBought = tickets;
    };

    // Getter & Setter
    int getTicketsBought(){
        return ticketsBought;
    };
    void setTicket(){
        ticketsBought ++;
    };

    void displayInformation()override{
        cout << "Tickets Bought: " << ticketsBought << endl;
    };
};

#endif
