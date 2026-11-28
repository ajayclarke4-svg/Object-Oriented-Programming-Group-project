#ifndef FOOTBALLLEAGUE_H
#define FOOTBALLLEAGUE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Exceptions.h"
#include "FootballTeam.h"
#include "MatchOfficial.h"
#include "Spectator.h"
#include "LeagueCommissioner.h"
#include "Stadium.h"
#include "Fixture.h"
#include "Ticket.h"
#include "StadiumShop.h"
using namespace std;

// ============================================================
//  FootballLeague — Master coordinator of the KPFL system
//
//  Business Rules Enforced:
//  1. Unregistered/Suspended teams cannot play fixtures
//  2. No team may appear in two fixtures on the same date/time
//  3. No official may officiate two fixtures on the same date/time
//  4. Ticket sales cannot exceed stadium capacity
//  5. Scores and quantities must be >= 0
//  6. Player age must be >= 16
//  7. Payment must be >= total charge
//  8. A fixture must have a recorded result before it can be completed
// ============================================================
class FootballLeague {
private:
    string leagueName;
    int season;

    vector<FootballTeam> teams;
    vector<Stadium> stadiums;
    vector<Fixture> fixtures;
    vector<MatchOfficial> officials;
    vector<Spectator> spectators;
    vector<Ticket> tickets;
    StadiumShop shop;
    LeagueCommissioner* commissioner;

    // Auto-incrementing ID counters
    int nextTeamId;
    int nextStadiumId;
    int nextFixtureId;
    int nextOfficialId;
    int nextSpectatorId;
    int nextTicketId;
    int nextProductId;

    // ---- Internal helper: find team by ID ----
    FootballTeam* findTeam(int id) {
        for (int i = 0; i < (int)teams.size(); i++) {
            if (teams[i].getTeamId() == id) {
                return &teams[i];
            }
        }
        return nullptr;
    }

    // ---- Internal helper: find stadium by ID ----
    Stadium* findStadium(int id) {
        for (int i = 0; i < (int)stadiums.size(); i++) {
            if (stadiums[i].getStadiumId() == id) {
                return &stadiums[i];
            }
        }
        return nullptr;
    }

    // ---- Internal helper: find fixture by ID ----
    Fixture* findFixture(int id) {
        for (int i = 0; i < (int)fixtures.size(); i++) {
            if (fixtures[i].getFixtureId() == id) {
                return &fixtures[i];
            }
        }
        return nullptr;
    }

    // ---- Internal helper: find official by ID ----
    MatchOfficial* findOfficial(int id) {
        for (int i = 0; i < (int)officials.size(); i++) {
            if (officials[i].getId() == id) {
                return &officials[i];
            }
        }
        return nullptr;
    }

    // ---- Internal helper: find spectator by ID ----
    Spectator* findSpectator(int id) {
        for (int i = 0; i < (int)spectators.size(); i++) {
            if (spectators[i].getId() == id) {
                return &spectators[i];
            }
        }
        return nullptr;
    }

    // ---- Business Rule 2: check team scheduling conflict ----
    // Returns true if the team already has a fixture at the same date and time
    bool teamHasConflict(int teamId, string date, string time, int excludeFixtureId = -1) {
        for (int i = 0; i < (int)fixtures.size(); i++) {
            if (fixtures[i].getFixtureId() == excludeFixtureId) continue;
            if (fixtures[i].getDate() == date && fixtures[i].getTime() == time) {
                if (fixtures[i].involvesTeam(teamId)) {
                    return true;
                }
            }
        }
        return false;
    }

    // ---- Business Rule 3: check official scheduling conflict ----
    // Returns true if the official is already assigned to a fixture at the same date/time
    bool officialHasConflict(int officialId, string date, string time, int excludeFixtureId = -1) {
        for (int i = 0; i < (int)fixtures.size(); i++) {
            if (fixtures[i].getFixtureId() == excludeFixtureId) continue;
            if (fixtures[i].getDate() == date && fixtures[i].getTime() == time) {
                if (fixtures[i].hasOfficial(officialId)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    // Constructor
    FootballLeague(string name, int leagueSeason) {
        this->leagueName = name;
        this->season = leagueSeason;
        this->commissioner = nullptr;
        this->nextTeamId = 1;
        this->nextStadiumId = 1;
        this->nextFixtureId = 1;
        this->nextOfficialId = 1;
        this->nextSpectatorId = 1;
        this->nextTicketId = 1;
        this->nextProductId = 1;
    }

    // Destructor
    ~FootballLeague() {
        if (commissioner != nullptr) {
            delete commissioner;
        }
    }

    // ---- Getters ----
    string getLeagueName() {
        return leagueName;
    }
    int getSeason() {
        return season;
    }
    vector<FootballTeam>& getTeams() {
        return teams;
    }
    vector<Stadium>& getStadiums() {
        return stadiums;
    }
    vector<Fixture>& getFixtures() {
        return fixtures;
    }
    vector<MatchOfficial>& getOfficials() {
        return officials;
    }
    vector<Spectator>& getSpectators() {
        return spectators;
    }
    StadiumShop& getShop() {
        return shop;
    }

    // ================================================================
    //  TEAM MANAGEMENT
    // ================================================================

    // Register a new team
    int registerTeam(string name, string parish, string regNumber, string status) {
        // Check for duplicate registration number
        for (int i = 0; i < (int)teams.size(); i++) {
            if (teams[i].getRegistrationNumber() == regNumber) {
                throw DuplicateEntryException("A team with registration number '" + regNumber + "' already exists.");
            }
        }
        int id = nextTeamId++;
        FootballTeam team(id, name, parish, regNumber, status);
        teams.push_back(team);
        cout << "Team '" << name << "' registered with ID " << id << "." << endl;
        return id;
    }

    // Update a team's league status
    void updateTeamStatus(int teamId, string newStatus) {
        FootballTeam* t = findTeam(teamId);
        if (t == nullptr) {
            throw TeamNotFoundException("Team with ID " + to_string(teamId) + " not found.");
        }
        t->setLeagueStatus(newStatus);
        cout << "Team '" << t->getName() << "' status updated to '" << newStatus << "'." << endl;
    }

    // Add a player to a team
    void addPlayerToTeam(int teamId, string playerName, int playerAge, string playerGender,
                         string position, int jerseyNumber, string status) {
        FootballTeam* t = findTeam(teamId);
        if (t == nullptr) {
            throw TeamNotFoundException("Team with ID " + to_string(teamId) + " not found.");
        }
        // Rule 6: player age >= 16 (enforced inside Player constructor)
        int pid = nextOfficialId++;
        Player p(pid, playerName, playerAge, playerGender, position, jerseyNumber, status, teamId);
        t->addPlayer(p);
        cout << "Player '" << playerName << "' added to team '" << t->getName() << "'." << endl;
    }

    // Add a coach to a team
    void addCoachToTeam(int teamId, string coachName, int coachAge, string coachGender,
                        string qualification, string role) {
        FootballTeam* t = findTeam(teamId);
        if (t == nullptr) {
            throw TeamNotFoundException("Team with ID " + to_string(teamId) + " not found.");
        }
        int cid = nextOfficialId++;
        Coach c(cid, coachName, coachAge, coachGender, qualification, role, teamId);
        t->addCoach(c);
        cout << "Coach '" << coachName << "' added to team '" << t->getName() << "'." << endl;
    }

    // Display all teams
    void displayAllTeams() {
        cout << "======= Registered Teams =======" << endl;
        if (teams.empty()) {
            cout << "No teams registered." << endl;
            return;
        }
        for (int i = 0; i < (int)teams.size(); i++) {
            teams[i].displayTeamInfo();
            cout << "--------------------------------" << endl;
        }
    }

    // ================================================================
    //  STADIUM MANAGEMENT
    // ================================================================

    int addStadium(string name, string location, int capacity,
                   string fieldCondition, double ticketPrice) {
        int id = nextStadiumId++;
        Stadium s(id, name, location, capacity, fieldCondition, ticketPrice);
        stadiums.push_back(s);
        cout << "Stadium '" << name << "' added with ID " << id << "." << endl;
        return id;
    }

    void displayAllStadiums() {
        cout << "======= Stadiums =======" << endl;
        if (stadiums.empty()) {
            cout << "No stadiums registered." << endl;
            return;
        }
        for (int i = 0; i < (int)stadiums.size(); i++) {
            stadiums[i].displayInformation();
            cout << "------------------------" << endl;
        }
    }

    // ================================================================
    //  OFFICIAL MANAGEMENT
    // ================================================================

    int registerOfficial(string name, int age, string gender,
                         string role, string rank) {
        int id = nextOfficialId++;
        MatchOfficial off(id, name, age, gender, role, rank);
        officials.push_back(off);
        cout << "Official '" << name << "' registered with ID " << id << "." << endl;
        return id;
    }

    void displayAllOfficials() {
        cout << "======= Match Officials =======" << endl;
        if (officials.empty()) {
            cout << "No officials registered." << endl;
            return;
        }
        for (int i = 0; i < (int)officials.size(); i++) {
            officials[i].displayInformation();
            cout << "-------------------------------" << endl;
        }
    }

    // ================================================================
    //  FIXTURE MANAGEMENT
    // ================================================================

    // Schedule a new fixture
    // Enforces Business Rules 1 and 2
    int scheduleFixture(int homeTeamId, int awayTeamId, int stadiumId,
                        string date, string time) {
        // ---- Rule 1: Both teams must be Registered ----
        FootballTeam* home = findTeam(homeTeamId);
        if (home == nullptr) {
            throw TeamNotFoundException("Home team with ID " + to_string(homeTeamId) + " not found.");
        }
        if (!home->isEligibleForFixture()) {
            throw TeamIneligibleException("Home team '" + home->getName() + "' is " + home->getLeagueStatus() + " and cannot play.");
        }

        FootballTeam* away = findTeam(awayTeamId);
        if (away == nullptr) {
            throw TeamNotFoundException("Away team with ID " + to_string(awayTeamId) + " not found.");
        }
        if (!away->isEligibleForFixture()) {
            throw TeamIneligibleException("Away team '" + away->getName() + "' is " + away->getLeagueStatus() + " and cannot play.");
        }

        // Check stadium exists
        Stadium* stad = findStadium(stadiumId);
        if (stad == nullptr) {
            throw StadiumNotFoundException("Stadium with ID " + to_string(stadiumId) + " not found.");
        }

        // ---- Rule 2: No team in two fixtures at same date/time ----
        if (teamHasConflict(homeTeamId, date, time)) {
            throw SchedulingConflictException("Home team '" + home->getName() + "' already has a fixture on " + date + " at " + time + ".");
        }
        if (teamHasConflict(awayTeamId, date, time)) {
            throw SchedulingConflictException("Away team '" + away->getName() + "' already has a fixture on " + date + " at " + time + ".");
        }

        int id = nextFixtureId++;
        Fixture f(id, homeTeamId, awayTeamId, stadiumId, date, time);
        fixtures.push_back(f);
        cout << "Fixture scheduled: " << home->getName() << " vs " << away->getName()
             << " on " << date << " at " << time << ". Fixture ID: " << id << "." << endl;
        return id;
    }

    // Assign an official to a fixture
    // Enforces Business Rule 3
    void assignOfficialToFixture(int fixtureId, int officialId) {
        Fixture* f = findFixture(fixtureId);
        if (f == nullptr) {
            throw FixtureNotFoundException("Fixture with ID " + to_string(fixtureId) + " not found.");
        }

        MatchOfficial* off = findOfficial(officialId);
        if (off == nullptr) {
            throw InvalidDataException("Official with ID " + to_string(officialId) + " not found.");
        }

        // ---- Rule 3: Official cannot be in two fixtures at same date/time ----
        if (officialHasConflict(officialId, f->getDate(), f->getTime(), fixtureId)) {
            throw SchedulingConflictException("Official '" + off->getName() + "' is already assigned to another fixture at " + f->getDate() + " " + f->getTime() + ".");
        }

        f->assignOfficial(officialId);
        cout << "Official '" << off->getName() << "' assigned to Fixture " << fixtureId << "." << endl;
    }

    // Record match result
    // Enforces Business Rule 5 (scores >= 0, enforced inside MatchResult)
    void recordFixtureResult(int fixtureId, int homeScore, int awayScore) {
        Fixture* f = findFixture(fixtureId);
        if (f == nullptr) {
            throw FixtureNotFoundException("Fixture with ID " + to_string(fixtureId) + " not found.");
        }
        if (f->getStatus() == "Completed") {
            throw InvalidDataException("Fixture " + to_string(fixtureId) + " is already completed.");
        }

        f->recordResult(homeScore, awayScore);

        // Update team standings
        FootballTeam* home = findTeam(f->getHomeTeamId());
        FootballTeam* away = findTeam(f->getAwayTeamId());
        if (home != nullptr) home->recordMatchResult(homeScore, awayScore);
        if (away != nullptr) away->recordMatchResult(awayScore, homeScore);

        cout << "Result recorded: " << homeScore << " - " << awayScore << " for Fixture " << fixtureId << "." << endl;
    }

    // Complete a fixture
    // Enforces Business Rule 8
    void completeFixture(int fixtureId) {
        Fixture* f = findFixture(fixtureId);
        if (f == nullptr) {
            throw FixtureNotFoundException("Fixture with ID " + to_string(fixtureId) + " not found.");
        }
        f->completeFixture();   // throws FixtureNotCompletedException if no result
        cout << "Fixture " << fixtureId << " marked as Completed." << endl;
    }

    void displayAllFixtures() {
        cout << "======= Fixtures =======" << endl;
        if (fixtures.empty()) {
            cout << "No fixtures scheduled." << endl;
            return;
        }
        for (int i = 0; i < (int)fixtures.size(); i++) {
            FootballTeam* home = findTeam(fixtures[i].getHomeTeamId());
            FootballTeam* away = findTeam(fixtures[i].getAwayTeamId());
            Stadium* stad = findStadium(fixtures[i].getStadiumId());
            fixtures[i].displayInformation(
                home ? home->getName() : "?",
                away ? away->getName() : "?",
                stad ? stad->getName() : "?"
            );
            cout << "------------------------" << endl;
        }
    }

    // ================================================================
    //  TICKET SALES
    // ================================================================

    // Sell a ticket to a spectator
    // Enforces Business Rule 4 (capacity), Rule 7 (payment)
    void sellTicket(int fixtureId, int spectatorId, string category, double payment) {
        Fixture* f = findFixture(fixtureId);
        if (f == nullptr) {
            throw FixtureNotFoundException("Fixture with ID " + to_string(fixtureId) + " not found.");
        }
        if (f->getStatus() != "Scheduled") {
            throw InvalidDataException("Tickets can only be sold for Scheduled fixtures.");
        }

        Stadium* stad = findStadium(f->getStadiumId());
        if (stad == nullptr) {
            throw StadiumNotFoundException("Stadium not found for this fixture.");
        }

        // Rule 4: capacity check (throws CapacityExceededException)
        stad->sellTickets(1);

        // Calculate cost with 15% GCT
        double basePrice = stad->getTicketPrice();
        double tax = basePrice * 0.15;
        double total = basePrice + tax;

        // Rule 7: payment must be >= total
        if (payment < total) {
            // Undo capacity change
            stad->setTicketsSold(stad->getTicketsSold() - 1);
            throw InsufficientPaymentException(
                "Payment of $" + to_string(payment) +
                " is less than ticket total of $" + to_string(total) + ".");
        }

        // Create ticket
        int tid = nextTicketId++;
        Ticket t(tid, fixtureId, category, basePrice);
        t.markAsSold(spectatorId);
        tickets.push_back(t);

        f->addTicketSales(1);

        // Update spectator's record
        Spectator* spec = findSpectator(spectatorId);
        if (spec != nullptr) {
            spec->recordPurchase(total);
        }

        double change = payment - total;
        cout << fixed << setprecision(2);
        cout << "====== TICKET SOLD ======" << endl;
        cout << "Ticket ID     : " << tid << endl;
        cout << "Fixture ID    : " << fixtureId << endl;
        cout << "Category      : " << category << endl;
        cout << "Base Price    : $" << basePrice << endl;
        cout << "GCT (15%)     : $" << tax << endl;
        cout << "Total         : $" << total << endl;
        cout << "Payment       : $" << payment << endl;
        cout << "Change        : $" << change << endl;
        cout << "=========================" << endl;
    }

    // ================================================================
    //  SPECTATOR MANAGEMENT
    // ================================================================

    int registerSpectator(string name, int age, string gender) {
        int id = nextSpectatorId++;
        Spectator s(id, name, age, gender);
        spectators.push_back(s);
        cout << "Spectator '" << name << "' registered with ID " << id << "." << endl;
        return id;
    }

    void displayAllSpectators() {
        cout << "======= Spectators =======" << endl;
        if (spectators.empty()) {
            cout << "No spectators registered." << endl;
            return;
        }
        for (int i = 0; i < (int)spectators.size(); i++) {
            spectators[i].displayInformation();
            cout << "------------------------" << endl;
        }
    }

    // ================================================================
    //  COMMISSIONER
    // ================================================================

    void setCommissioner(string name, int age, string gender,
                         string location, string badge, int years) {
        if (commissioner != nullptr) {
            delete commissioner;
        }
        commissioner = new LeagueCommissioner(1, name, age, gender, location, badge, years);
        cout << "League Commissioner set to: " << name << "." << endl;
    }

    void displayCommissioner() {
        if (commissioner == nullptr) {
            cout << "No commissioner appointed." << endl;
            return;
        }
        commissioner->displayInformation();
    }

    // ================================================================
    //  SHOP MANAGEMENT
    // ================================================================

    void addMerchandise(string name, double price, int stock, string type, string size) {
        int id = nextProductId++;
        Merchandise* m = new Merchandise(id, name, price, stock, type, size);
        shop.addProduct(m);
        cout << "Merchandise '" << name << "' added to shop with ID " << id << "." << endl;
    }

    void addFoodItem(string name, double price, int stock, bool isBeverage, string portion) {
        int id = nextProductId++;
        FoodItem* f = new FoodItem(id, name, price, stock, isBeverage, portion);
        shop.addProduct(f);
        cout << "Food item '" << name << "' added to shop with ID " << id << "." << endl;
    }

    // Shop sale
    void processShopSale(int productId, int qty, double payment) {
        double sub = 0, tax = 0, total = 0, change = 0;
        string receipt = shop.completeSale(productId, qty, payment, sub, tax, total, change);
        cout << receipt;
    }

    // ================================================================
    //  LEAGUE TABLE (Standings)
    // ================================================================

    void displayLeagueTable() {
        if (teams.empty()) {
            cout << "No teams in the league." << endl;
            return;
        }

        // Sort teams by points (desc), then goal difference (desc)
        vector<FootballTeam*> sorted;
        for (int i = 0; i < (int)teams.size(); i++) {
            sorted.push_back(&teams[i]);
        }
        sort(sorted.begin(), sorted.end(), [](FootballTeam* a, FootballTeam* b) {
            if (a->getPoints() != b->getPoints()) {
                return a->getPoints() > b->getPoints();
            }
            return a->getGoalDifference() > b->getGoalDifference();
        });

        cout << "======= " << leagueName << " — Season " << season << " Standings =======" << endl;
        cout << left
             << setw(4)  << "Pos"
             << setw(22) << "Team"
             << setw(5)  << "MP"
             << setw(5)  << "W"
             << setw(5)  << "D"
             << setw(5)  << "L"
             << setw(5)  << "GF"
             << setw(5)  << "GA"
             << setw(5)  << "GD"
             << setw(5)  << "Pts"
             << endl;
        cout << string(66, '-') << endl;

        for (int i = 0; i < (int)sorted.size(); i++) {
            FootballTeam* t = sorted[i];
            cout << left
                 << setw(4)  << (i + 1)
                 << setw(22) << t->getName()
                 << setw(5)  << t->getMatchesPlayed()
                 << setw(5)  << t->getWins()
                 << setw(5)  << t->getDraws()
                 << setw(5)  << t->getLosses()
                 << setw(5)  << t->getGoalsFor()
                 << setw(5)  << t->getGoalsAgainst()
                 << setw(5)  << t->getGoalDifference()
                 << setw(5)  << t->getPoints()
                 << endl;
        }
    }

    // ================================================================
    //  REPORTS
    // ================================================================

    void displayTopScorers() {
        cout << "======= Top Goal Scorers =======" << endl;
        vector<pair<string, int>> scorers;
        for (int i = 0; i < (int)teams.size(); i++) {
            vector<Player>& players = teams[i].getPlayers();
            for (int j = 0; j < (int)players.size(); j++) {
                if (players[j].getGoals() > 0) {
                    scorers.push_back({players[j].getName(), players[j].getGoals()});
                }
            }
        }
        sort(scorers.begin(), scorers.end(), [](pair<string,int> a, pair<string,int> b) {
            return a.second > b.second;
        });
        if (scorers.empty()) {
            cout << "No goals scored yet." << endl;
            return;
        }
        for (int i = 0; i < (int)scorers.size(); i++) {
            cout << (i+1) << ". " << scorers[i].first << " — " << scorers[i].second << " goals" << endl;
        }
    }

    void displayFixtureReport() {
        int scheduled = 0, completed = 0, cancelled = 0;
        for (int i = 0; i < (int)fixtures.size(); i++) {
            if (fixtures[i].getStatus() == "Scheduled") scheduled++;
            else if (fixtures[i].getStatus() == "Completed") completed++;
            else cancelled++;
        }
        cout << "======= Fixture Report =======" << endl;
        cout << "Total Fixtures : " << fixtures.size() << endl;
        cout << "Scheduled      : " << scheduled << endl;
        cout << "Completed      : " << completed << endl;
        cout << "Cancelled      : " << cancelled << endl;
    }

    // ================================================================
    //  FILE I/O — Save and Load all data
    // ================================================================

    void saveAllData() {
        // Save teams
        ofstream teamFile("Data/teams.txt");
        for (int i = 0; i < (int)teams.size(); i++) {
            teamFile << teams[i].toRecord() << "\n";
            // Save players and coaches inside each team
        }
        teamFile.close();

        // Save players
        ofstream playerFile("Data/players.txt");
        for (int i = 0; i < (int)teams.size(); i++) {
            vector<Player>& players = teams[i].getPlayers();
            for (int j = 0; j < (int)players.size(); j++) {
                playerFile << players[j].toRecord() << "\n";
            }
        }
        playerFile.close();

        // Save coaches
        ofstream coachFile("Data/coaches.txt");
        for (int i = 0; i < (int)teams.size(); i++) {
            vector<Coach>& coaches = teams[i].getCoaches();
            for (int j = 0; j < (int)coaches.size(); j++) {
                coachFile << coaches[j].toRecord() << "\n";
            }
        }
        coachFile.close();

        // Save stadiums
        ofstream stadFile("Data/stadiums.txt");
        for (int i = 0; i < (int)stadiums.size(); i++) {
            stadFile << stadiums[i].toRecord() << "\n";
        }
        stadFile.close();

        // Save fixtures
        ofstream fixFile("Data/fixtures.txt");
        for (int i = 0; i < (int)fixtures.size(); i++) {
            fixFile << fixtures[i].toRecord() << "\n";
        }
        fixFile.close();

        // Save officials
        ofstream offFile("Data/officials.txt");
        for (int i = 0; i < (int)officials.size(); i++) {
            offFile << officials[i].toRecord() << "\n";
        }
        offFile.close();

        // Save spectators
        ofstream specFile("Data/spectators.txt");
        for (int i = 0; i < (int)spectators.size(); i++) {
            specFile << spectators[i].toRecord() << "\n";
        }
        specFile.close();

        // Save tickets
        ofstream tickFile("Data/tickets.txt");
        for (int i = 0; i < (int)tickets.size(); i++) {
            tickFile << tickets[i].toRecord() << "\n";
        }
        tickFile.close();

        // Save shop products
        ofstream shopFile("Data/shop.txt");
        vector<Product*>& inv = shop.getInventory();
        for (int i = 0; i < (int)inv.size(); i++) {
            shopFile << inv[i]->toRecord() << "\n";
        }
        shopFile.close();

        cout << "All data saved successfully." << endl;
    }

    void loadAllData() {
        string line;

        // Load teams
        ifstream teamFile("Data/teams.txt");
        if (teamFile.is_open()) {
            while (getline(teamFile, line)) {
                if (!line.empty()) {
                    FootballTeam t;
                    t.fromRecord(line);
                    teams.push_back(t);
                    if (t.getTeamId() >= nextTeamId) nextTeamId = t.getTeamId() + 1;
                }
            }
            teamFile.close();
        }

        // Load players into their teams
        ifstream playerFile("Data/players.txt");
        if (playerFile.is_open()) {
            while (getline(playerFile, line)) {
                if (!line.empty()) {
                    Player p;
                    p.fromRecord(line);
                    FootballTeam* t = findTeam(p.getTeamId());
                    if (t != nullptr) {
                        // Add without duplicate jersey check for loading
                        t->getPlayers().push_back(p);
                    }
                }
            }
            playerFile.close();
        }

        // Load coaches into their teams
        ifstream coachFile("Data/coaches.txt");
        if (coachFile.is_open()) {
            while (getline(coachFile, line)) {
                if (!line.empty()) {
                    Coach c;
                    c.fromRecord(line);
                    FootballTeam* t = findTeam(c.getTeamId());
                    if (t != nullptr) {
                        t->getCoaches().push_back(c);
                    }
                }
            }
            coachFile.close();
        }

        // Load stadiums
        ifstream stadFile("Data/stadiums.txt");
        if (stadFile.is_open()) {
            while (getline(stadFile, line)) {
                if (!line.empty()) {
                    Stadium s;
                    s.fromRecord(line);
                    stadiums.push_back(s);
                    if (s.getStadiumId() >= nextStadiumId) nextStadiumId = s.getStadiumId() + 1;
                }
            }
            stadFile.close();
        }

        // Load fixtures
        ifstream fixFile("Data/fixtures.txt");
        if (fixFile.is_open()) {
            while (getline(fixFile, line)) {
                if (!line.empty()) {
                    Fixture f;
                    f.fromRecord(line);
                    fixtures.push_back(f);
                    if (f.getFixtureId() >= nextFixtureId) nextFixtureId = f.getFixtureId() + 1;
                }
            }
            fixFile.close();
        }

        // Load officials
        ifstream offFile("Data/officials.txt");
        if (offFile.is_open()) {
            while (getline(offFile, line)) {
                if (!line.empty()) {
                    MatchOfficial off;
                    off.fromRecord(line);
                    officials.push_back(off);
                    if (off.getId() >= nextOfficialId) nextOfficialId = off.getId() + 1;
                }
            }
            offFile.close();
        }

        // Load spectators
        ifstream specFile("Data/spectators.txt");
        if (specFile.is_open()) {
            while (getline(specFile, line)) {
                if (!line.empty()) {
                    Spectator s;
                    s.fromRecord(line);
                    spectators.push_back(s);
                    if (s.getId() >= nextSpectatorId) nextSpectatorId = s.getId() + 1;
                }
            }
            specFile.close();
        }

        // Load tickets
        ifstream tickFile("Data/tickets.txt");
        if (tickFile.is_open()) {
            while (getline(tickFile, line)) {
                if (!line.empty()) {
                    Ticket t;
                    t.fromRecord(line);
                    tickets.push_back(t);
                    if (t.getTicketId() >= nextTicketId) nextTicketId = t.getTicketId() + 1;
                }
            }
            tickFile.close();
        }

        // Load shop products
        ifstream shopFile("Data/shop.txt");
        if (shopFile.is_open()) {
            while (getline(shopFile, line)) {
                if (!line.empty()) {
                    if (line.substr(0, 5) == "MERCH") {
                        Merchandise* m = new Merchandise();
                        m->fromRecord();
                        shop.getInventory().push_back(m);
                        if (m->getProductId() >= nextProductId) nextProductId = m->getProductId() + 1;
                    } else if (line.substr(0, 4) == "FOOD") {
                        FoodItem* f = new FoodItem();
                        f->fromRecord();
                        shop.getInventory().push_back(f);
                        if (f->getProductId() >= nextProductId) nextProductId = f->getProductId() + 1;
                    }
                }
            }
            shopFile.close();
        }

        cout << "Data loaded. Teams: " << teams.size()
             << ", Stadiums: " << stadiums.size()
             << ", Fixtures: " << fixtures.size()
             << ", Officials: " << officials.size() << endl;
    }
};

#endif
