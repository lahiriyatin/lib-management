#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Book {
    int bookID;
    string title;
    string author;
    string ISBN;
    int quantity;
};

void showMenu() {
    cout << "\nBook Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book by Title\n";
    cout << "3. Display All Books\n";
    cout << "4. Remove Book\n";
    cout << "5. Edit Book\n";
    cout << "6. Save Books to File\n";
    cout << "7. Load Books from File\n";
    cout << "8. Exit\n";
    cout << "Choose an option: ";
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


void addBook(vector<Book>& books) {
    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.bookID;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter ISBN: ";
    getline(cin, newBook.ISBN);
    cout << "Enter Quantity: ";
    cin >> newBook.quantity;

    books.push_back(newBook);
    cout << "Book added successfully!\n";
}

void searchByTitle(const vector<Book>& books, const string& title) {
    string lowerTitle = toLowerCase(title);
    bool found = false;

    for (const auto& book : books) {
        if (toLowerCase(book.title).find(lowerTitle) != string::npos) {
            cout << "\nBook ID: " << book.bookID
                 << "\nTitle: " << book.title
                 << "\nAuthor: " << book.author
                 << "\nISBN: " << book.ISBN
                 << "\nQuantity: " << book.quantity << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }
}


void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    for (const auto& book : books) {
        cout << "\nBook ID: " << book.bookID
             << "\nTitle: " << book.title
             << "\nAuthor: " << book.author
             << "\nISBN: " << book.ISBN
             << "\nQuantity: " << book.quantity << endl;
        cout << "----------------------------------------------------\n";
    }
}


void removeBook(vector<Book>& books, int bookID) {
    auto it = find_if(books.begin(), books.end(), [bookID](const Book& book) {
        return book.bookID == bookID;
    });

    if (it != books.end()) {
        books.erase(it);
        cout << "Book removed successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

void editBook(vector<Book>& books, int bookID) {
    for (auto& book : books) {
        if (book.bookID == bookID) {
            cout << "Editing book details:\n";
            cout << "Enter new title (or press Enter to keep it the same): ";
            cin.ignore(); // To handle the newline character
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) book.title = newTitle;

            cout << "Enter new author (or press Enter to keep it the same): ";
            string newAuthor;
            getline(cin, newAuthor);
            if (!newAuthor.empty()) book.author = newAuthor;

            cout << "Enter new ISBN (or press Enter to keep it the same): ";
            string newISBN;
            getline(cin, newISBN);
            if (!newISBN.empty()) book.ISBN = newISBN;

            cout << "Enter new quantity (or press Enter to keep it the same): ";
            string newQuantity;
            getline(cin, newQuantity);
            if (!newQuantity.empty()) book.quantity = stoi(newQuantity);

            cout << "Book details updated successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

int main() {
    vector<Book> books;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2: {
                cin.ignore(); // To handle the newline character
                string title;
                cout << "Enter the title of the book: ";
                getline(cin, title);
                searchByTitle(books, title);
                break;
            }
            case 3:
                cout << "----------------------------------------------------";
                displayBooks(books);
                cout << "----------------------------------------------------";
                break;
            case 4: {
                int bookID;
                cout << "Enter the Book ID to remove: ";
                cin >> bookID;
                removeBook(books, bookID);
                break;
            }
            case 5: {
                int bookID;
                cout << "Enter the Book ID to edit: ";
                cin >> bookID;
                editBook(books, bookID);
                break;
            }
            case 6:
                cout << "Feature disabled.\n";
                break;
            case 7:
                cout << "Feature disabled.\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
