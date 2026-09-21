#include "Book.h"

Book::Book()
    : Resource(), isbn("") {
}

Book::Book(int id, const string& isbn, const string& title,
           const string& author, const string& publisher, int totalCopies)
    : Resource(id, title, author, publisher, totalCopies), isbn(isbn) {
    if (!isValidIsbn(isbn)) {
        cout << "[Book] ISBN格式可能不正确: " << isbn << endl;
    }
}

Book::~Book() {}

string Book::getIsbn() const { return isbn; }

void Book::setIsbn(const string& isbn) {
    if (isValidIsbn(isbn)) {
        this->isbn = isbn;
    } else {
        cout << "[Book] ISBN格式不正确" << endl;
    }
}

string Book::getType() const { return "图书"; }

string Book::getInfo() const {
    return "ISBN:" + isbn;
}

void Book::display() const {
    cout << "ID: " << id
         << " | 类型: 图书"
         << " | ISBN: " << isbn
         << " | 书名: " << title
         << " | 作者: " << author
         << " | 出版社: " << publisher
         << " | 库存: " << availableCopies << "/" << totalCopies
         << endl;
}

void Book::displayBrief() const {
    cout << "[" << id << "] [图书] " << title << " - " << author
         << " (可借: " << availableCopies << ")" << endl;
}

string Book::serialize() const {
    return "BOOK|" + to_string(id) + "|" + isbn + "|" + title + "|" +
           author + "|" + publisher + "|" + to_string(totalCopies) + "|" +
           to_string(availableCopies);
}

bool Book::isValidIsbn(const string& isbn) {
    return !isbn.empty() && isbn.length() >= 10;
}
