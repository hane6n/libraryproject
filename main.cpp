#include <iostream>
#include "library.h"
#include "storage.h"
#include "reports.h"
#include "utils.h"

int main() {
    LibraryState state;
    loadDatabase(state, "library_db.txt");
    int choice;
    while (true) {
        std::cout << "\n\033[1;34m--- Library System (Day: " << state.currentDay << ") ---\033[0m\n";
        std::cout << "1. Add Book\n2. Add Member\n3. Checkout\n4. Return\n5. Overdue Report\n6. Export Overdue\n7. Next Day\n8. Save & Exit\nChoice: ";
        if (!(std::cin >> choice)) break;
        try {
            if (choice == 1) {
                Book b;
                std::cout << "ISBN: "; std::cin >> b.isbn;
                std::cout << "Title: "; std::getline(std::cin >> std::ws, b.title);
                std::cout << "Author: "; std::getline(std::cin >> std::ws, b.author);
                std::cout << "Total: "; std::cin >> b.totalCopies;
                b.availableCopies = b.totalCopies;
                addBook(state, b);
                sortData(state.books, [](const Book& a, const Book& b) { return a.isbn < b.isbn; });
                std::cout << "\033[1;32mDone!\033[0m\n";
            } else if (choice == 2) {
                Member m;
                std::cout << "ID: "; std::cin >> m.id;
                std::cout << "Name: "; std::getline(std::cin >> std::ws, m.name);
                addMember(state, m);
                std::cout << "\033[1;32mDone!\033[0m\n";
            } else if (choice == 3) {
                std::string mId, isbn;
                std::cout << "Member ID & ISBN: "; std::cin >> mId >> isbn;
                checkoutBook(state, mId, isbn);
                std::cout << "\033[1;32mSuccess!\033[0m\n";
            } else if (choice == 4) {
                std::string mId, isbn;
                std::cout << "Member ID & ISBN: "; std::cin >> mId >> isbn;
                returnBook(state, mId, isbn);
                std::cout << "\033[1;32mSuccess!\033[0m\n";
            } else if (choice == 5) generateOverdueReport(state);
            else if (choice == 6) exportOverdueBooks(state, "overdue.csv");
            else if (choice == 7) { state.currentDay++; }
            else if (choice == 8) { saveDatabase(state, "library_db.txt"); break; }
        } catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
    }
    return 0;
}