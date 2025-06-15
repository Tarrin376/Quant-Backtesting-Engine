#ifndef STATS_H
#define STATS_H

#include <ostream>
#include <iomanip>

struct Stats {
    double percReturn{};
    double initialCapital{};
    double finalCapital{};
    int numTrades{};
    double totalProfit{};
    double winRate{};
    int winningPositions{};
    int losingPositions{};

    friend std::ostream& operator<<(std::ostream& out, const Stats& stats) {
        out << std::fixed << std::setprecision(2);
        out << "===== Backtest Statistics =====\n";
        out << "Initial Capital     : $" << stats.initialCapital << '\n';
        out << "Final Capital       : $" << stats.finalCapital << '\n';
        out << "Final Profit/Loss   : $" << stats.totalProfit << '\n';
        out << "Percentage Return   : " << stats.percReturn << "%\n";
        out << "Number of Trades    : " << stats.numTrades << '\n';
        out << "Win Rate            : " << stats.winRate << "%\n";
        out << "Winning Positions   : " << stats.winningPositions << '\n';
        out << "Losing Positions    : " << stats.losingPositions << '\n';
        out << "===============================\n";
        return out;
    }
};

#endif