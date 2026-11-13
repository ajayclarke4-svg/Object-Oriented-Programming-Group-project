#include <iostream>
#include <limits>
#include <string>

#include "Ticket.h"
#include "Product.h"
#include "Merchandise.h"
#include "Fooditem.h"
#include "StadiumShop.h"
using namespace std;

int Frontscreen();
void TeamAndPeople();
void StadiumsAndOfficials();
void FixturesAndResults();
void Tickets();
void StadiumShop();
void Reports();
void SaveData();
void ReloadData();      

int main (){
   int choice;
   do {
    choice = Frontscreen();
    switch (choice) {
        case 1:
            TeamAndPeople();
            break;
        case 2:
            StadiumsAndOfficials();
            break;
        case 3:
            FixturesAndResults();
            break;
        case 4:
            Tickets();
            break;
        case 5:
            StadiumShop();
            break;
        case 6:
            Reports();
            break;
        case 7: 
            SaveData();
            break;
        case 8:
            ReloadData();
            break;
        case 0:  
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
   } 
   while (choice != 0);
           
    return 0;
}
int Frontscreen(){
    int Selection;
    cout << "\n=========KINGSTON PREMIER FOOTBALL LEAGUE=======\n";
    cout << "1. Team and people" << endl;
    cout << "2. Stadiums and officials" << endl;
    cout << "3. Fixtures and results" << endl;
    cout << "4. Tickets " << endl;
    cout << "5. Stadium shop" << endl;
    cout << "6. Reports " << endl;
    cout << "7. Save data " << endl;
    cout << "8. Reload data " << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    if (!(cin >> Selection)) {
        cin.clear();
        cin.ignore(8, '\n');
        Selection = -1;
    }
    cin.ignore(8, '\n');
    return Selection;
}
void TeamAndPeople() {
    int selection;

    cout << "1. Register team" << endl;
    cout << "2. update team" << endl;
    cout << "3. search team" << endl;
    cout << "4. show teams" << endl;
    cout << "5. approve team registration" << endl; 
    cout << "6. add player" << endl;
    cout << "7. Add coach" << endl;
    cout << "8. Update player or coach" << endl;
    cout << "9. Remove player or coach" << endl;
    cout << "0. Back" << endl;

    if (!(cin >> selection)) {
        cin.clear();
        cin.ignore(8, '\n');
        selection = -1;
    }
    cin.ignore(8, '\n');
    
    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
         
            break;
        case 4:
          
            break;
        case 5:
          
            break;
        case 6:
           
            break;
        case 7:
            
            break;
        case 8:
           
            break;
        case 9:
          
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
    
}
void StadiumsAndOfficials() {
    int selection;
    cout << "1 Register stadium "<< endl;                  
    cout << "2 Show stadiums" << endl;
    cout << "3 Register match official" << endl;
    cout << "4 Show match officials" << endl;
    cout << "0 Back" << endl;

    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
          
            break;
        case 4:
          
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void FixturesAndResults() {
    int selection;

    cout << "1 Create fixture" << endl;
    cout << "2 Assign match officials" << endl;
    cout << "3 Show fixtures" << endl;
    cout << "4 Record result" << endl;
    cout << "5 Show standings" << endl;
    cout << "0 Back" << endl;

    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
          
            break;
        case 4:
          
            break;
        case 5:
          
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }

}
void Tickets() {
   int selection;

    cout << "1 Sell ticket" << endl;
    cout << "2 Seats left for a fixture" << endl;
    cout << "0 Back" << endl;

    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void StadiumShop() {
   int selection;

    cout << "1 Show products" << endl;
    cout << "2 Add product" << endl;
    cout << "3 Update stock" << endl;
    cout << "4 Make a sale" << endl;

    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
          
            break;
        case 4:
          
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void Reports() {
    int selection;

    cout << "1 League standings" << endl;
    cout << "2 Ticket sales by fixture" << endl;
    cout << "3 Shop stock and sales" << endl;
    cout << "4 Teams and squads" << endl;
    cout << "0 Back" << endl;

    switch (selection) {
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
          
            break;
        case 4:
          
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}
void SaveData() {
    cout << "Save data functionality goes here." << endl;
}
void ReloadData() {
    cout << "Reload data functionality goes here." << endl;
}
