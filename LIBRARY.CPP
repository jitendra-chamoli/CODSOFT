#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool available;
};

struct Borrower {
    string name;
    string borrowedISBN;
    time_t borrowDate;
};

void displayMenu() {
    cout << "\nLibrary Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Search Book" << endl;
    cout << "3. Checkout Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. View Borrowers" << endl;
    cout << "6. Exit" << endl;
    cout << "Choose an option: ";
}

void addBook(vector<Book>& books) {
    Book newBook;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    cout << "Enter book ISBN: ";
    getline(cin, newBook.isbn);
    newBook.available = true;
    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

void searchBook(const vector<Book>& books) {
    string query;
    cout << "Enter book title, author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);

    for (const auto& book : books) {
        if (book.title == query || book.author == query || book.isbn == query) {
            cout << "\nBook Found!" << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "ISBN: " << book.isbn << endl;
            cout << "Status: " << (book.available ? "Available" : "Checked Out") << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void checkoutBook(vector<Book>& books, vector<Borrower>& borrowers) {
    string isbn;
    cout << "Enter ISBN of the book to checkout: ";
    cin >> isbn;

    for (auto& book : books) {
        if (book.isbn == isbn) {
            if (book.available) {
                book.available = false;
                Borrower newBorrower;
                cout << "Enter borrower's name: ";
                cin.ignore();
                getline(cin, newBorrower.name);
                newBorrower.borrowedISBN = isbn;
                newBorrower.borrowDate = time(0);
                borrowers.push_back(newBorrower);
                cout << "Book checked out successfully!" << endl;
            } else {
                cout << "Book is already checked out!" << endl;
            }
            return;
        }
    }
    cout << "Book with the given ISBN not found!" << endl;
}

int calculateFine(time_t borrowDate) {
    const int finePerDay = 2;
    time_t currentTime = time(0);
    double secondsInDay = 60 * 60 * 24;
    int daysElapsed = (currentTime - borrowDate) / secondsInDay;

    if (daysElapsed > 14) {
        return (daysElapsed - 14) * finePerDay;
    }
    return 0;
}

void returnBook(vector<Book>& books, vector<Borrower>& borrowers) {
    string isbn;
    cout << "Enter ISBN of the book to return: ";
    cin >> isbn;

    auto it = find_if(borrowers.begin(), borrowers.end(), [&isbn](const Borrower& borrower) {
        return borrower.borrowedISBN == isbn;
    });

    if (it != borrowers.end()) {
        int fine = calculateFine(it->borrowDate);
        if (fine > 0) {
            cout << "Book is overdue! Fine amount: " << fine << " units" << endl;
        }
        cout << "Book returned successfully!" << endl;

        borrowers.erase(it); 

        for (auto& book : books) {
            if (book.isbn == isbn) {
                book.available = true; 
            }
        }
    } else {
        cout << "Borrower with the given ISBN not found!" << endl;
    }
}

void viewBorrowers(const vector<Borrower>& borrowers) {
    if (borrowers.empty()) {
        cout << "No borrowers found!" << endl;
        return;
    }

    cout << "\nList of Borrowers:" << endl;
    for (const auto& borrower : borrowers) {
        cout << "Name: " << borrower.name << ", Book ISBN: " << borrower.borrowedISBN << endl;
    }
}

int main() {
    vector<Book> books;
    vector<Borrower> borrowers;

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                searchBook(books);
                break;
            case 3:
                checkoutBook(books, borrowers);
                break;
            case 4:
                returnBook(books, borrowers);
                break;
            case 5:
                viewBorrowers(borrowers);
                break;
            case 6:
                cout << "Exiting Library Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option! Please choose a valid option." << endl;
        }
    } while (choice != 6);

    return 0;
}
