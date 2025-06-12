#include "core/Portfolio.h"

Portfolio::Portfolio(double initialBalance) : 
    _initialBalance{ initialBalance }, 
    _currentBalance{ initialBalance } {};

void Portfolio::decreaseBalance(double amount) {
    _currentBalance -= amount;
}

void Portfolio::increaseBalance(double amount) {
    _currentBalance += amount;
}