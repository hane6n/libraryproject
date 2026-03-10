#include "library.h"
#include <stdexcept>
#include <iostream>

void addBook(LibraryState& state, const Book& b) {
    state.books.push_back(b);
}

void addMember(LibraryState& state, const Member& m) {
    state.members.push_back(m);
}

Book* findBook(LibraryState& state, const std::string& isbn) {
    for (auto& b : state.books) {
        if (b.isbn == isbn) return &b;
    }
    return nullptr;
}

Member* findMember(LibraryState& state, const std::string& id) {
    for (auto& m : state.members) {
        if (m.id == id) return &m;
    }
    return nullptr;
}

void checkoutBook(LibraryState& state, const std::string& memberId, const std::string& isbn) {
    Book* b = findBook(state, isbn);
    if (!b) throw std::runtime_error("Book not found");
    if (b->availableCopies <= 0) throw std::runtime_error("No copies available");
    
    if (!findMember(state, memberId)) throw std::runtime_error("Member not found");

    b->availableCopies--;
    state.loans.push_back({isbn, memberId, state.currentDay, state.currentDay + state.LOAN_PERIOD});
}

void returnBook(LibraryState& state, const std::string& memberId, const std::string& isbn) {
    Book* b = findBook(state, isbn);
    bool found = false;
    for (size_t i = 0; i < state.loans.size(); i++) {
        if (state.loans[i].isbn == isbn && state.loans[i].memberId == memberId) {
            if (state.currentDay > state.loans[i].dueDay) {
                int fine = (state.currentDay - state.loans[i].dueDay) * 5;
                std::cout << "\033[1;33mOverdue! Fine: " << fine << " L.E.\033[0m" << std::endl;
            }
            state.loans.erase(state.loans.begin() + i);
            if (b) b->availableCopies++;
            found = true;
            break;
        }
    }
    if (!found) throw std::runtime_error("Loan record not found");
}