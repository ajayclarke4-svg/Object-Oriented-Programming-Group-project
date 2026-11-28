#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <limits>
#include "FootballLeague.h"
using namespace std;

// ============================================================
//  Menu — Interactive console menu for the KPFL system
//  Handles all user input and routes to FootballLeague methods.
// ============================================================
class Menu {
private:
    FootballLeague& league;

    // ---- Safe input helpers ----
    int readInt(string prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin.eof()) {
                cout << "\nEnd of input reached. Exiting." << endl;
                exit(0);
            }
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a whole number." << endl;
            }
        }
    }

    double readDouble(string prompt) {
        double value;
        while (true) {
            cout << prompt;
            if (cin.eof()) {
                cout << "\nEnd of input reached. Exiting." << endl;
                exit(0);
            }
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
            }
        }
    }

    string readString(string prompt) {
        string value;
        cout << prompt;
        if (cin.eof()) {
            cout << "\nEnd of input reached. Exiting." << endl;
            exit(0);
        }
        getline(cin, value);
        return value;
    }

    // ---- Sub-menus ----

    void teamMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Team Management ---" << endl;
            cout << "1. Register Team" << endl;
            cout << "2. Display All Teams" << endl;
            cout << "3. Update Team Status" << endl;
            cout << "4. Add Player to Team" << endl;
            cout << "5. Add Coach to Team" << endl;
            cout << "6. Display Team Players" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    string name = readString("Team Name: ");
                    string parish = readString("Parish: ");
                    string regNum = readString("Registration Number: ");
                    cout << "Status (Registered/Suspended/Unregistered): ";
                    string status = readString("");
                    league.registerTeam(name, parish, regNum, status);

                } else if (choice == 2) {
                    league.displayAllTeams();

                } else if (choice == 3) {
                    int tid = readInt("Team ID: ");
                    cout << "New Status (Registered/Suspended/Unregistered): ";
                    string status = readString("");
                    league.updateTeamStatus(tid, status);

                } else if (choice == 4) {
                    int tid = readInt("Team ID: ");
                    string name = readString("Player Name: ");
                    int age = readInt("Age: ");
                    string gender = readString("Gender (Male/Female): ");
                    string pos = readString("Position: ");
                    int jersey = readInt("Jersey Number (1-99): ");
                    string status = readString("Status (Active/Suspended): ");
                    league.addPlayerToTeam(tid, name, age, gender, pos, jersey, status);

                } else if (choice == 5) {
                    int tid = readInt("Team ID: ");
                    string name = readString("Coach Name: ");
                    int age = readInt("Age: ");
                    string gender = readString("Gender: ");
                    string qual = readString("Qualification: ");
                    string role = readString("Role (Head Coach/Assistant Coach): ");
                    league.addCoachToTeam(tid, name, age, gender, qual, role);

                } else if (choice == 6) {
                    int tid = readInt("Team ID: ");
                    league.displayTeamPlayers(tid);

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void stadiumMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Stadium Management ---" << endl;
            cout << "1. Add Stadium" << endl;
            cout << "2. Display All Stadiums" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    string name = readString("Stadium Name: ");
                    string location = readString("Location: ");
                    int capacity = readInt("Capacity: ");
                    string condition = readString("Field Condition (Excellent/Good/Fair/Poor): ");
                    double price = readDouble("Ticket Price: $");
                    league.addStadium(name, location, capacity, condition, price);

                } else if (choice == 2) {
                    league.displayAllStadiums();

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void officialMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Match Officials ---" << endl;
            cout << "1. Register Official" << endl;
            cout << "2. Display All Officials" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    string name = readString("Name: ");
                    int age = readInt("Age: ");
                    string gender = readString("Gender: ");
                    string role = readString("Role (Referee/Linesman/Fourth Official): ");
                    string rank = readString("Rank (FIFA/National/Regional): ");
                    league.registerOfficial(name, age, gender, role, rank);

                } else if (choice == 2) {
                    league.displayAllOfficials();

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void fixtureMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Fixture Management ---" << endl;
            cout << "1. Schedule Fixture" << endl;
            cout << "2. Display All Fixtures" << endl;
            cout << "3. Assign Official to Fixture" << endl;
            cout << "4. Record Match Result" << endl;
            cout << "5. Complete Fixture" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    int homeId = readInt("Home Team ID: ");
                    int awayId = readInt("Away Team ID: ");
                    int stadId = readInt("Stadium ID: ");
                    string date = readString("Date (YYYY-MM-DD): ");
                    string time = readString("Time (HH:MM): ");
                    league.scheduleFixture(homeId, awayId, stadId, date, time);

                } else if (choice == 2) {
                    league.displayAllFixtures();

                } else if (choice == 3) {
                    int fid = readInt("Fixture ID: ");
                    int oid = readInt("Official ID: ");
                    league.assignOfficialToFixture(fid, oid);

                } else if (choice == 4) {
                    int fid = readInt("Fixture ID: ");
                    int homeScore = readInt("Home Team Score: ");
                    int awayScore = readInt("Away Team Score: ");
                    league.recordFixtureResult(fid, homeScore, awayScore);

                } else if (choice == 5) {
                    int fid = readInt("Fixture ID: ");
                    league.completeFixture(fid);

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void ticketMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Ticket Sales ---" << endl;
            cout << "1. Register Spectator" << endl;
            cout << "2. Sell Ticket" << endl;
            cout << "3. Display All Spectators" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    string name = readString("Spectator Name: ");
                    int age = readInt("Age: ");
                    string gender = readString("Gender: ");
                    league.registerSpectator(name, age, gender);

                } else if (choice == 2) {
                    int fid = readInt("Fixture ID: ");
                    int sid = readInt("Spectator ID: ");
                    cout << "Category (VIP/Grandstand/Bleachers): ";
                    string cat = readString("");
                    double payment = readDouble("Payment: $");
                    league.sellTicket(fid, sid, cat, payment);

                } else if (choice == 3) {
                    league.displayAllSpectators();

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void shopMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Stadium Shop ---" << endl;
            cout << "1. Add Merchandise" << endl;
            cout << "2. Add Food Item" << endl;
            cout << "3. Buy Product" << endl;
            cout << "4. Restock Product" << endl;
            cout << "5. Display Inventory" << endl;
            cout << "6. Financial Summary" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    string name = readString("Product Name: ");
                    double price = readDouble("Price: $");
                    int stock = readInt("Stock Quantity: ");
                    string type = readString("Item Type (Jersey/Cap/Scarf/Mug): ");
                    string size = readString("Size (S/M/L/XL/One Size): ");
                    league.addMerchandise(name, price, stock, type, size);

                } else if (choice == 2) {
                    string name = readString("Product Name: ");
                    double price = readDouble("Price: $");
                    int stock = readInt("Stock Quantity: ");
                    int bev = readInt("Is Beverage? (1=Yes, 0=No): ");
                    string portion = readString("Portion Size (Small/Medium/Large): ");
                    league.addFoodItem(name, price, stock, bev == 1, portion);

                } else if (choice == 3) {
                    league.getShop().displayInventory();
                    int pid = readInt("Product ID: ");
                    int qty = readInt("Quantity: ");
                    double payment = readDouble("Payment: $");
                    league.processShopSale(pid, qty, payment);

                } else if (choice == 4) {
                    int pid = readInt("Product ID: ");
                    int qty = readInt("Restock Quantity: ");
                    league.getShop().restock(pid, qty);

                } else if (choice == 5) {
                    league.getShop().displayInventory();

                } else if (choice == 6) {
                    league.getShop().displayFinancialSummary();

                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

    void reportsMenu() {
        bool back = false;
        while (!back) {
            cout << "\n--- Reports ---" << endl;
            cout << "1. League Table (Standings)" << endl;
            cout << "2. Top Scorers" << endl;
            cout << "3. Fixture Report" << endl;
            cout << "4. Commissioner Info" << endl;
            cout << "0. Back" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    league.displayLeagueTable();
                } else if (choice == 2) {
                    league.displayTopScorers();
                } else if (choice == 3) {
                    league.displayFixtureReport();
                } else if (choice == 4) {
                    league.displayCommissioner();
                } else if (choice == 0) {
                    back = true;
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            }
        }
    }

public:
    // Constructor
    Menu(FootballLeague& leagueRef) : league(leagueRef) {}

    // ---- Main menu loop ----
    void run() {
        cout << "================================================" << endl;
        cout << "  Welcome to the " << league.getLeagueName() << endl;
        cout << "  Season: " << league.getSeason() << endl;
        cout << "================================================" << endl;

        bool running = true;
        while (running) {
            cout << "\n========= MAIN MENU =========" << endl;
            cout << "1. Team Management" << endl;
            cout << "2. Stadium Management" << endl;
            cout << "3. Match Officials" << endl;
            cout << "4. Fixture Management" << endl;
            cout << "5. Ticket Sales" << endl;
            cout << "6. Stadium Shop" << endl;
            cout << "7. Reports & Standings" << endl;
            cout << "8. Save Data" << endl;
            cout << "9. Load Data" << endl;
            cout << "0. Exit" << endl;
            cout << "==============================" << endl;
            int choice = readInt("Enter choice: ");
            cout << endl;

            try {
                if (choice == 1) {
                    teamMenu();
                } else if (choice == 2) {
                    stadiumMenu();
                } else if (choice == 3) {
                    officialMenu();
                } else if (choice == 4) {
                    fixtureMenu();
                } else if (choice == 5) {
                    ticketMenu();
                } else if (choice == 6) {
                    shopMenu();
                } else if (choice == 7) {
                    reportsMenu();
                } else if (choice == 8) {
                    league.saveAllData();
                } else if (choice == 9) {
                    league.loadAllData();
                } else if (choice == 0) {
                    cout << "Saving data before exit..." << endl;
                    league.saveAllData();
                    cout << "Goodbye!" << endl;
                    running = false;
                } else {
                    cout << "Invalid choice. Please select 0-9." << endl;
                }
            } catch (LeagueException& e) {
                cout << "[Error] " << e.what() << endl;
            } catch (exception& e) {
                cout << "[System Error] " << e.what() << endl;
            }
        }
    }
};

#endif
