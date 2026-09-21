#ifndef BOOK_H
#define BOOK_H

#include "Resource.h"

class Book : public Resource {
private:
    string isbn;

public:
    Book();
    Book(int id, const string& isbn, const string& title,
         const string& author, const string& publisher,
         int totalCopies);
    ~Book();

    string getIsbn() const;
    void setIsbn(const string& isbn);

    string getType() const override;
    string getInfo() const override;
    void display() const override;
    void displayBrief() const override;
    string serialize() const override;

    static bool isValidIsbn(const string& isbn);
};

#endif
