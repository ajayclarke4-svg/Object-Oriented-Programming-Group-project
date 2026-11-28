#include <iostream>
#include "FootballLeague.h"
#include "Menu.h"
using namespace std;

// ============================================================
//  main.cpp — Entry point for the KPFL Management System
//  Ajay Clarke — Student ID: 2504343
//  Group Project: Kingston Premier Football League
// ============================================================
int main() {
    FootballLeague league("Kingston Premier Football League", 2026);
    league.loadAllData();

    Menu menu(league);
    menu.run();

    return 0;
}
