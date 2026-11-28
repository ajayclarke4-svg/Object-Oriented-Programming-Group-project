#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
using namespace std;

// ============================================================
//  Base league exception — all custom exceptions inherit this
// ============================================================
class LeagueException : public runtime_error {
public:
    LeagueException(string msg) : runtime_error(msg) {}
};

// ============================================================
//  Data / validation errors
// ============================================================
class InvalidDataException : public LeagueException {
public:
    InvalidDataException(string msg) : LeagueException(msg) {}
};

class NegativeValueException : public LeagueException {
public:
    NegativeValueException(string msg) : LeagueException(msg) {}
};

class DuplicateEntryException : public LeagueException {
public:
    DuplicateEntryException(string msg) : LeagueException(msg) {}
};

// ============================================================
//  Team / player errors
// ============================================================
class TeamNotFoundException : public LeagueException {
public:
    TeamNotFoundException(string msg) : LeagueException(msg) {}
};

class PlayerNotFoundException : public LeagueException {
public:
    PlayerNotFoundException(string msg) : LeagueException(msg) {}
};

class TeamIneligibleException : public LeagueException {
public:
    TeamIneligibleException(string msg) : LeagueException(msg) {}
};

// ============================================================
//  Fixture / scheduling errors
// ============================================================
class FixtureNotFoundException : public LeagueException {
public:
    FixtureNotFoundException(string msg) : LeagueException(msg) {}
};

class SchedulingConflictException : public LeagueException {
public:
    SchedulingConflictException(string msg) : LeagueException(msg) {}
};

class FixtureNotCompletedException : public LeagueException {
public:
    FixtureNotCompletedException(string msg) : LeagueException(msg) {}
};

// ============================================================
//  Stadium / ticket errors
// ============================================================
class StadiumNotFoundException : public LeagueException {
public:
    StadiumNotFoundException(string msg) : LeagueException(msg) {}
};

class CapacityExceededException : public LeagueException {
public:
    CapacityExceededException(string msg) : LeagueException(msg) {}
};

// ============================================================
//  Financial errors
// ============================================================
class InsufficientPaymentException : public LeagueException {
public:
    InsufficientPaymentException(string msg) : LeagueException(msg) {}
};

class ProductNotFoundException : public LeagueException {
public:
    ProductNotFoundException(string msg) : LeagueException(msg) {}
};

class InsufficientStockException : public LeagueException {
public:
    InsufficientStockException(string msg) : LeagueException(msg) {}
};

#endif
