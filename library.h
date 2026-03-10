#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>
#include <vector>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    int totalCopies;
    int availableCopies;
};

struct Member {
    std::string id;
    std::string name;
};

struct Loan {
    std::string isbn;
    std::string memberId;
    int checkoutDay;
    int dueDay;
};

struct LibraryState {
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;
    int currentDay = 0;
    const int LOAN_PERIOD = 14;
};

void addBook(LibraryState& state, const Book& b);
void addMember(LibraryState& state, const Member& m);
Book* findBook(LibraryState& state, const std::string& isbn);
Member* findMember(LibraryState& state, const std::string& id);
void checkoutBook(LibraryState& state, const std::string& memberId, const std::string& isbn);
void returnBook(LibraryState& state, const std::string& memberId, const std::string& isbn);

#endif