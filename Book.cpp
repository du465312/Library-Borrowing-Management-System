
#include "Book.h"

Book::Book()
    : Resource(), isbn(""), author(""), publisher("") {
}

Book::Book(int id, const string& isbn, const string& title,
           const string& author, const string& publisher, int totalCopies)
    : Resource(id, title, totalCopies), isbn(isbn), author(author), publisher(publisher) {
}

string Book::getIsbn() const { return isbn; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }

void Book::setAuthor(const string& author) { this->author = author; }
void Book::display() const {
    cout << "[普通图书] ";
    Resource::display();
    cout << " | ISBN: " << isbn
         << " | 作者: " << author
         << " | 出版社: " << publisher
         << endl;
}

bool Book::isValidIsbn(const string& isbn) {
    return !isbn.empty() && isbn.length() >= 10;
}
