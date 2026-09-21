#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
using namespace std;

// 图书类（已删除 Resource 抽象基类与 Magazine/ElectronicResource 分支）
class Book {
private:
    int id;
    string isbn;
    string title;
    string author;
    string publisher;
    int totalCopies;
    int availableCopies;

public:
    Book();
    Book(int id, const string& isbn, const string& title,
         const string& author, const string& publisher, int totalCopies);

    int getId() const;
    string getIsbn() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;

    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setTotalCopies(int totalCopies);

    bool isAvailable() const;
    bool borrow();
    bool returnBook();

    void display() const;

    static bool isValidIsbn(const string& isbn);
};

#endif
