#include "Book.h"

Book::Book()
    : id(0), isbn(""), title(""), author(""), publisher(""),
      totalCopies(0), availableCopies(0) {
}

Book::Book(int id, const string& isbn, const string& title,
           const string& author, const string& publisher, int totalCopies)
    : id(id), isbn(isbn), title(title), author(author), publisher(publisher) {
    if (totalCopies > 0) {
        this->totalCopies = totalCopies;
        this->availableCopies = totalCopies;
    } else {
        this->totalCopies = 1;
        this->availableCopies = 1;
    }
}

int Book::getId() const { return id; }
string Book::getIsbn() const { return isbn; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
int Book::getTotalCopies() const { return totalCopies; }
int Book::getAvailableCopies() const { return availableCopies; }

void Book::setTitle(const string& title) { this->title = title; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setTotalCopies(int totalCopies) {
    if (totalCopies > 0) {
        int diff = totalCopies - this->totalCopies;
        this->totalCopies = totalCopies;
        this->availableCopies += diff;
        if (this->availableCopies < 0) this->availableCopies = 0;
    }
}

bool Book::isAvailable() const { return availableCopies > 0; }

bool Book::borrow() {
    if (availableCopies > 0) {
        availableCopies--;
        return true;
    }
    return false;
}

bool Book::returnBook() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        return true;
    }
    return false;
}

void Book::display() const {
    cout << "图书ID: " << id
         << " | ISBN: " << isbn
         << " | 书名: " << title
         << " | 作者: " << author
         << " | 出版社: " << publisher
         << " | 库存: " << availableCopies << "/" << totalCopies
         << endl;
}

bool Book::isValidIsbn(const string& isbn) {
    return !isbn.empty() && isbn.length() >= 10;
}
