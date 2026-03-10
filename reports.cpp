#include "reports.h"
#include <iostream>
#include <fstream>

void generateOverdueReport(const LibraryState& state) {
    std::cout << "\033[1;34m--- Overdue Report ---\033[0m" << std::endl;
    for (const auto& loan : state.loans) {
        if (state.currentDay > loan.dueDay) {
            std::cout << "ISBN: " << loan.isbn << " | Member: " << loan.memberId 
                      << " | Late: " << (state.currentDay - loan.dueDay) << " days" << std::endl;
        }
    }
}

void exportOverdueBooks(const LibraryState& state, const std::string& filename) {
    std::ofstream file(filename);
    file << "ISBN,MemberID,DaysOverdue,Fine\n";
    for (const auto& loan : state.loans) {
        if (state.currentDay > loan.dueDay) {
            int late = state.currentDay - loan.dueDay;
            file << loan.isbn << "," << loan.memberId << "," << late << "," << late * 5 << "\n";
        }
    }
    file.close();
}