#include <iostream>
#include "FootballLeague.h"
#include "FootballTeam.h"
#include "Menu.h"
#include "Exceptions.h"

using namespace std;

int main() {
    cout << "======================================================================\n";
    cout << "             KINGSTON PREMIER FOOTBALL LEAGUE (KPFL)                  \n";
    cout << "               Match-Day Management System 2026                       \n";
    cout << "               Six-Week Group Project Deliverable                     \n";
    cout << "======================================================================\n";
    cout << "Project Team:\n";
    cout << " - Adrian Wilson:           Person, Player, Coach, Team, Spectator\n";
    cout << " - Ajay Clarke (2504343):   Product, Merchandise, FoodItem, Ticket, Shop\n";
    cout << " - Destiny Yates (2509282): Stadium, MatchOfficial, Fixture, MatchResult\n";
    cout << " - Leah Kusah:              FootballLeague, Commissioner, Menu, Exceptions\n";
    cout << " - Shuana-Kaye Grant:       FileManager, Storable, Data Storage & Evals\n";
    cout << "======================================================================\n";

    try {
        FootballLeague league("Kingston Premier Football League", 2026);

        cout << "\nAttempting to automatically preload persistent league records...\n";
        try {
            league.loadAllData();
        } catch (const exception& ex) {
            cout << "[Note] Could not preload existing records (" << ex.what()
                 << "). Starting with fresh or partial data.\n";
        }

        Menu menu(league);
        menu.run();

        // Optional prompt to save upon exiting
        if (!cin.eof()) {
            cout << "\nDo you wish to save all changes before exiting? (y/n): ";
            char saveChoice;
            if (cin >> saveChoice && (saveChoice == 'y' || saveChoice == 'Y')) {
                league.saveAllData();
            }
        }
        cout << "\nExiting KPFL Management System. Goodbye!\n";

    } catch (const exception& ex) {
        cerr << "\nFATAL ERROR: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
