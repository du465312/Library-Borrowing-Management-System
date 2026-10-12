#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "Resource.h"
using namespace std;

class Book : public Resource {
private:
    string isbn;
    string author;
    string publisher;

public:
    Book();
    Book(int id, const string& isbn, const string& title,
         const string& author, const string& publisher, int totalCopies);

    string getIsbn() const;
    string getAuthor() const;
    string getPublisher() const;

    void setAuthor(const string& author);

    void display() const;

    static bool isValidIsbn(const string& isbn);
};

#endif
