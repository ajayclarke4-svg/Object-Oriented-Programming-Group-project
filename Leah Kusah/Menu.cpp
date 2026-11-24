#include "Menu.h"
#include "Exceptions.h"
#include "FootballTeam.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

Menu::Menu(FootballLeague& footballLeague) : league{footballLeague} {}

int Menu::readInt(const string& prompt) {
    int value;
    while (true) {
        if (cin.eof()) return 0;
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            if (cin.eof()) return 0;
            cout << "Invalid whole number input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double Menu::readDouble(const string& prompt) {
    double value;
    while (true) {
        if (cin.eof()) return 0.0;
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            if (cin.eof()) return 0.0;
            cout << "Invalid decimal number input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string Menu::readString(const string& prompt) {
    if (cin.eof()) return "";
    cout << prompt;
    string line;
    if (!getline(cin, line)) return "";
    // trim leading/trailing whitespace if needed
    size_t first = line.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = line.find_last_not_of(" \t\r\n");
    return line.substr(first, (last - first + 1));
}

void Menu::pause() {
    if (cin.eof()) return;
    cout << "\nPress Enter to continue...";
    cin.get();
}

void Menu::run() {
    int choice = -1;
    do {
        cout << "\n=======================================================\n";
        cout << "       KINGSTON PREMIER FOOTBALL LEAGUE (KPFL)         \n";
        cout << "            Match-Day Operations System                \n";
        cout << "=======================================================\n";
        cout << "1. Team and Personnel Management\n";
        cout << "2. Stadiums and Match Officials\n";
        cout << "3. Fixtures, Results and Standings\n";
        cout << "4. Match-Day Ticketing and Capacity\n";
        cout << "5. Stadium Shop and Merchandise\n";
        cout << "6. Management Reports and Analytics\n";
        cout << "7. Save All League Data to Files\n";
        cout << "8. Reload All League Data from Files\n";
        cout << "0. Exit Application\n";
        cout << "=======================================================\n";

        choice = readInt("Select an option (0-8): ");

        try {
            switch (choice) {
                case 1:
                    handleTeamAndPersonnel();
                    break;
                case 2:
                    handleStadiumsAndOfficials();
                    break;
                case 3:
                    handleFixturesAndResults();
                    break;
                case 4:
                    handleTickets();
                    break;
                case 5:
                    handleStadiumShop();
                    break;
                case 6:
                    handleReports();
                    break;
                case 7:
                    league.saveAllData();
                    pause();
                    break;
                case 8:
                    league.loadAllData();
                    pause();
                    break;
                case 0:
                    cout << "\nThank you for using the KPFL Management System. Good luck this season!\n";
                    break;
                default:
                    cout << "Invalid choice. Please select from 0 to 8.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
            pause();
        } catch (const exception& ex) {
            cout << "\n[UNEXPECTED ERROR] " << ex.what() << "\n";
            pause();
        }
    } while (choice != 0);
}

void Menu::handleTeamAndPersonnel() {
    int option = -1;
    do {
        cout << "\n--- TEAM AND PERSONNEL MANAGEMENT ---\n";
        cout << "1. Register New Football Team\n";
        cout << "2. Update Team Information\n";
        cout << "3. Search for Team (by ID or Name)\n";
        cout << "4. Display All Registered Teams\n";
        cout << "5. Approve Team Registration (Commissioner)\n";
        cout << "6. Set Team League Status (Registered / Suspended / Unregistered)\n";
        cout << "7. Add Player to Team\n";
        cout << "8. Add Coach to Team\n";
        cout << "9. Update Player in Team\n";
        cout << "10. Remove Player from Team\n";
        cout << "11. Display Team Roster & Staff\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1: {
                    int id = readInt("Enter Team ID: ");
                    string name = readString("Enter Team Name: ");
                    string parish = readString("Enter Parish (e.g. Kingston): ");
                    string regNum = readString("Enter Registration #: ");
                    string status = readString("Initial Status (Registered/Unregistered): ");
                    if (status.empty()) status = "Unregistered";
                    FootballTeam team(id, name, parish, regNum, status);
                    league.registerTeam(team);
                    cout << "Team registered successfully!\n";
                    break;
                }
                case 2: {
                    int id = readInt("Enter Team ID to update: ");
                    FootballTeam* t = league.findTeamById(id);
                    if (!t) throw TeamNotFoundException("Team ID not found.");
                    string name = readString("Enter new Team Name (" + t->getName() + "): ");
                    if (name.empty()) name = t->getName();
                    string parish = readString("Enter new Parish (" + t->getParish() + "): ");
                    if (parish.empty()) parish = t->getParish();
                    string reg = readString("Enter new Reg # (" + t->getRegistrationNumber() + "): ");
                    if (reg.empty()) reg = t->getRegistrationNumber();
                    string status = readString("Enter new Status (" + t->getLeagueStatus() + "): ");
                    if (status.empty()) status = t->getLeagueStatus();

                    FootballTeam updated(id, name, parish, reg, status);
                    league.updateTeam(updated);
                    cout << "Team updated successfully!\n";
                    break;
                }
                case 3: {
                    string query = readString("Enter Team ID or Team Name to search: ");
                    FootballTeam* t = league.findTeamByName(query);
                    if (!t) {
                        try {
                            int id = FileManager::toInt(query);
                            t = league.findTeamById(id);
                        } catch (...) {}
                    }
                    if (t) {
                        cout << "\nTeam Found:\n";
                        t->displayInformation();
                    } else {
                        cout << "Team matching '" << query << "' was not found.\n";
                    }
                    break;
                }
                case 4:
                    league.displayAllTeams();
                    break;
                case 5: {
                    int id = readInt("Enter Team ID for Commissioner Approval: ");
                    league.approveTeamRegistration(id);
                    break;
                }
                case 6: {
                    int id = readInt("Enter Team ID: ");
                    string status = readString("Enter Status (Registered, Unregistered, Suspended): ");
                    league.setTeamStatus(id, status);
                    cout << "Team status updated to " << status << ".\n";
                    break;
                }
                case 7: {
                    int teamId = readInt("Enter Team ID: ");
                    int pId = readInt("Enter Player ID: ");
                    string pName = readString("Enter Player Name: ");
                    int pAge = readInt("Enter Age (Min 16): ");
                    string pGender = readString("Enter Gender (Male/Female): ");
                    string pos = readString("Enter Position (Forward, Midfielder, Defender, Goalkeeper): ");
                    int jersey = readInt("Enter Jersey Number (1-99): ");
                    int goals = readInt("Enter Goals Scored: ");
                    string status = readString("Enter Playing Status (Active/Injured/Suspended): ");
                    if (status.empty()) status = "Active";

                    Player p(pId, pName, pAge, pGender, pos, jersey, goals, status, teamId);
                    league.addPlayerToTeam(teamId, p);
                    cout << "Player " << pName << " added to team!\n";
                    break;
                }
                case 8: {
                    int teamId = readInt("Enter Team ID: ");
                    int cId = readInt("Enter Coach ID: ");
                    string cName = readString("Enter Coach Name: ");
                    int cAge = readInt("Enter Age: ");
                    string cGender = readString("Enter Gender: ");
                    string qual = readString("Enter Qualification (e.g. CONCACAF A, JFF Level 2): ");
                    string role = readString("Enter Coaching Role (e.g. Head Coach, Assistant): ");

                    Coach c(cId, cName, cAge, cGender, qual, role, teamId);
                    league.addCoachToTeam(teamId, c);
                    cout << "Coach " << cName << " added to team!\n";
                    break;
                }
                case 9: {
                    int teamId = readInt("Enter Team ID: ");
                    int pId = readInt("Enter Player ID to update: ");
                    FootballTeam* t = league.findTeamById(teamId);
                    if (!t) throw TeamNotFoundException("Team not found.");
                    Player* p = t->findPlayer(pId);
                    if (!p) throw PlayerNotFoundException("Player not found in team.");

                    string pName = readString("New Name (" + p->getName() + "): ");
                    if (pName.empty()) pName = p->getName();
                    int pAge = readInt("New Age: ");
                    string pos = readString("New Position (" + p->getPosition() + "): ");
                    if (pos.empty()) pos = p->getPosition();
                    int jersey = readInt("New Jersey #: ");
                    int goals = readInt("New Goals Scored: ");
                    string status = readString("New Status (" + p->getPlayingStatus() + "): ");
                    if (status.empty()) status = p->getPlayingStatus();

                    Player up(pId, pName, pAge, p->getGender(), pos, jersey, goals, status, teamId);
                    league.updatePlayerInTeam(teamId, up);
                    cout << "Player updated successfully!\n";
                    break;
                }
                case 10: {
                    int teamId = readInt("Enter Team ID: ");
                    int pId = readInt("Enter Player ID to remove: ");
                    league.removePlayerFromTeam(teamId, pId);
                    cout << "Player removed successfully.\n";
                    break;
                }
                case 11: {
                    int teamId = readInt("Enter Team ID: ");
                    FootballTeam* t = league.findTeamById(teamId);
                    if (!t) throw TeamNotFoundException("Team not found.");
                    t->displayRoster();
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}

void Menu::handleStadiumsAndOfficials() {
    int option = -1;
    do {
        cout << "\n--- STADIUMS AND MATCH OFFICIALS ---\n";
        cout << "1. Register New Stadium\n";
        cout << "2. Display All Stadiums\n";
        cout << "3. Update Stadium Field Condition\n";
        cout << "4. Request Practice Permission for a Team\n";
        cout << "5. Register Match Official\n";
        cout << "6. Display All Match Officials\n";
        cout << "7. Inspect Stadium (Commissioner)\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1: {
                    int id = readInt("Enter Stadium ID: ");
                    string name = readString("Enter Stadium Name: ");
                    string loc = readString("Enter Location: ");
                    int cap = readInt("Enter Seating Capacity: ");
                    string cond = readString("Enter Field Condition (Excellent/Good/Fair/Poor): ");
                    double price = readDouble("Enter Base Ticket Price ($): ");
                    Stadium s(id, name, loc, cap, cond, price);
                    league.registerStadium(s);
                    cout << "Stadium registered successfully!\n";
                    break;
                }
                case 2:
                    league.displayAllStadiums();
                    break;
                case 3: {
                    int id = readInt("Enter Stadium ID: ");
                    string cond = readString("Enter New Field Condition: ");
                    league.updateStadiumCondition(id, cond);
                    cout << "Stadium condition updated!\n";
                    break;
                }
                case 4: {
                    int teamId = readInt("Enter Team ID requesting practice: ");
                    int stadId = readInt("Enter Stadium ID: ");
                    league.requestPracticePermission(teamId, stadId);
                    break;
                }
                case 5: {
                    int id = readInt("Enter Official ID: ");
                    string name = readString("Enter Full Name: ");
                    int age = readInt("Enter Age: ");
                    string gender = readString("Enter Gender: ");
                    string role = readString("Enter Role (Referee/Assistant Referee 1/Assistant Referee 2/Fourth Official): ");
                    string rank = readString("Enter Rank (FIFA/National/Parish): ");
                    MatchOfficial mo(id, name, age, gender, role, rank, true);
                    league.registerOfficial(mo);
                    cout << "Match official registered successfully!\n";
                    break;
                }
                case 6:
                    league.displayAllOfficials();
                    break;
                case 7: {
                    int id = readInt("Enter Stadium ID to inspect: ");
                    Stadium* s = league.findStadiumById(id);
                    if (!s) throw StadiumNotFoundException("Stadium not found.");
                    league.getCommissioner()->inspectStadium(*s);
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}

void Menu::handleFixturesAndResults() {
    int option = -1;
    do {
        cout << "\n--- FIXTURES, RESULTS AND STANDINGS ---\n";
        cout << "1. Create New Fixture (with conflict & eligibility validation)\n";
        cout << "2. Assign Match Official to Fixture\n";
        cout << "3. Display All Fixtures & Schedule\n";
        cout << "4. Record Match Result (Score & Standings Update)\n";
        cout << "5. Display Official KPFL Standings\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1: {
                    int hId = readInt("Enter Home Team ID: ");
                    int aId = readInt("Enter Away Team ID: ");
                    int sId = readInt("Enter Stadium ID: ");
                    string date = readString("Enter Date (YYYY-MM-DD): ");
                    string time = readString("Enter Time (HH:MM): ");

                    int fId = league.createFixture(hId, aId, sId, date, time);
                    cout << "Fixture #" << fId << " successfully scheduled!\n";
                    break;
                }
                case 2: {
                    int fId = readInt("Enter Fixture ID: ");
                    int oId = readInt("Enter Official ID: ");
                    league.assignOfficialToFixture(fId, oId);
                    break;
                }
                case 3:
                    league.displayAllFixtures();
                    break;
                case 4: {
                    int fId = readInt("Enter Fixture ID: ");
                    int hScore = readInt("Enter Home Team Score: ");
                    int aScore = readInt("Enter Away Team Score: ");
                    league.recordMatchResult(fId, hScore, aScore);
                    break;
                }
                case 5:
                    league.displayStandings();
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}

void Menu::handleTickets() {
    int option = -1;
    do {
        cout << "\n--- MATCH-DAY TICKETING ---\n";
        cout << "1. Sell Match Tickets (Monitors Stadium Capacity & Calculates 15% GCT)\n";
        cout << "2. Check Remaining Seats for a Fixture\n";
        cout << "3. Display Issued Tickets\n";
        cout << "4. Register New Spectator\n";
        cout << "5. Display All Spectators\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1: {
                    int fId = readInt("Enter Fixture ID: ");
                    int rem = league.getSeatsRemainingForFixture(fId);
                    cout << "Seats remaining at fixture venue: " << rem << "\n";
                    cout << "Categories: 1. Bleachers (0.8x) | 2. Grandstand (1.2x) | 3. VIP (1.6x)\n";
                    int catChoice = readInt("Select Category (1-3): ");
                    string cat = "Bleachers";
                    if (catChoice == 2) cat = "Grandstand";
                    else if (catChoice == 3) cat = "VIP";

                    int qty = readInt("Enter Number of Tickets: ");
                    int specId = readInt("Enter Spectator ID: ");
                    double payment = readDouble("Enter Payment Tendered ($): ");

                    double subtotal, tax, total, change;
                    string receipt = league.sellTicket(fId, cat, qty, specId, payment, subtotal, tax, total, change);
                    cout << receipt;
                    break;
                }
                case 2: {
                    int fId = readInt("Enter Fixture ID: ");
                    int left = league.getSeatsRemainingForFixture(fId);
                    cout << "Fixture #" << fId << " has " << left << " seats available.\n";
                    break;
                }
                case 3:
                    league.displayTickets();
                    break;
                case 4: {
                    int id = readInt("Enter Spectator ID: ");
                    string name = readString("Enter Full Name: ");
                    int age = readInt("Enter Age: ");
                    string gender = readString("Enter Gender: ");
                    Spectator sp(id, name, age, gender);
                    league.registerSpectator(sp);
                    cout << "Spectator registered successfully!\n";
                    break;
                }
                case 5:
                    league.displayAllSpectators();
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}

void Menu::handleStadiumShop() {
    int option = -1;
    do {
        cout << "\n--- STADIUM SHOP & MERCHANDISE ---\n";
        cout << "1. Display Shop Products & Inventory\n";
        cout << "2. Complete Shop Purchase (Calculates Subtotal, 15% GCT & Change)\n";
        cout << "3. Add New Product (Merchandise or Food/Beverage)\n";
        cout << "4. Restock Existing Product\n";
        cout << "5. View Shop Financial & Tax Audit\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1:
                    league.displayShopInventory();
                    break;
                case 2: {
                    int pId = readInt("Enter Product ID to purchase: ");
                    int qty = readInt("Enter Quantity: ");
                    double payment = readDouble("Enter Cash Tendered ($): ");

                    double subtotal, tax, total, change;
                    string receipt = league.processShopSale(pId, qty, payment, subtotal, tax, total, change);
                    cout << receipt;
                    break;
                }
                case 3: {
                    cout << "Product Type: 1. Merchandise | 2. Food / Beverage\n";
                    int typeChoice = readInt("Choice (1 or 2): ");
                    int pId = readInt("Enter Product ID: ");
                    string name = readString("Enter Product Name: ");
                    double price = readDouble("Enter Price ($): ");
                    int stock = readInt("Enter Initial Stock: ");

                    if (typeChoice == 1) {
                        string itemType = readString("Enter Item Type (Jersey/Cap/Flag/Scarf): ");
                        string size = readString("Enter Size (S/M/L/XL/One Size): ");
                        Merchandise* m = new Merchandise(pId, name, price, stock, itemType, size);
                        league.addProductToShop(m);
                        cout << "Merchandise added to inventory!\n";
                    } else {
                        string isBev = readString("Is this a beverage? (y/n): ");
                        bool bev = (isBev == "y" || isBev == "Y" || isBev == "yes");
                        string portion = readString("Enter Portion/Volume (e.g. Standard, 500ml): ");
                        FoodItem* fi = new FoodItem(pId, name, price, stock, bev, portion);
                        league.addProductToShop(fi);
                        cout << "Food/Beverage added to inventory!\n";
                    }
                    break;
                }
                case 4: {
                    int pId = readInt("Enter Product ID: ");
                    int qty = readInt("Enter Quantity to Add: ");
                    league.restockShopProduct(pId, qty);
                    cout << "Product restocked successfully!\n";
                    break;
                }
                case 5:
                    league.getShop().displayFinancialSummary();
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}

void Menu::handleReports() {
    int option = -1;
    do {
        cout << "\n--- KPFL MANAGEMENT REPORTS & ANALYTICS ---\n";
        cout << "1. Report 1: League Standings & Top Scorers (Golden Boot)\n";
        cout << "2. Report 2: Match-Day Attendance, Ticket Revenue & Stadium Utilization\n";
        cout << "3. Report 3: Stadium Shop Inventory Valuation & Financial Audit\n";
        cout << "4. Report 4: Complete Club Squads & Personnel Roster\n";
        cout << "5. Report 5: Match Schedule & Officials Conflict Audit\n";
        cout << "0. Back to Main Menu\n";

        option = readInt("Choice: ");
        try {
            switch (option) {
                case 1:
                    league.generateStandingsAndTopScorersReport();
                    break;
                case 2:
                    league.generateTicketSalesAndAttendanceReport();
                    break;
                case 3:
                    league.generateShopInventoryAndFinancialReport();
                    break;
                case 4:
                    league.generateClubSquadsAndPersonnelReport();
                    break;
                case 5:
                    league.generateMatchScheduleAndOfficialsReport();
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const LeagueException& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
        if (option != 0) pause();
    } while (option != 0);
}
