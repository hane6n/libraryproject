#include "storage.h"
#include "utils.h"
#include <fstream>

void saveDatabase(const LibraryState& state, const std::string& dbPath) {
    std::ofstream file(dbPath);
    file << "DAY\n" << state.currentDay << "\nBOOKS\n";
    for (const auto& b : state.books) {
        file << b.isbn << "," << b.title << "," << b.author << "," << b.totalCopies << "," << b.availableCopies << "\n";
    }
    file << "MEMBERS\n";
    for (const auto& m : state.members) {
        file << m.id << "," << m.name << "\n";
    }
    file << "LOANS\n";
    for (const auto& l : state.loans) {
        file << l.isbn << "," << l.memberId << "," << l.checkoutDay << "," << l.dueDay << "\n";
    }
    file << "END";
    file.close();
}

void loadDatabase(LibraryState& state, const std::string& dbPath) {
    std::ifstream file(dbPath);
    if (!file.is_open()) return;
    std::string line, section = "";
    while (std::getline(file, line)) {
        if (line == "DAY") {
            std::string dayVal;
            std::getline(file, dayVal);
            state.currentDay = std::stoi(dayVal);
        }
        else if (line == "BOOKS" || line == "MEMBERS" || line == "LOANS") section = line;
        else if (line == "END") break;
        else {
            std::vector<std::string> d = split(line, ',');
            if (section == "BOOKS" && d.size() >= 5) 
                state.books.push_back({d[0], d[1], d[2], std::stoi(d[3]), std::stoi(d[4])});
            else if (section == "MEMBERS" && d.size() >= 2) 
                state.members.push_back({d[0], d[1]});
            else if (section == "LOANS" && d.size() >= 4) 
                state.loans.push_back({d[0], d[1], std::stoi(d[2]), std::stoi(d[3])});
        }
    }
}