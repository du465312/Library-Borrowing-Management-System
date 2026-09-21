#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>
using namespace std;

class Resource {
protected:
    int id;
    string title;
    string author;
    string publisher;
    int totalCopies;
    int availableCopies;

public:
    Resource();
    Resource(int id, const string& title, const string& author,
             const string& publisher, int totalCopies);
    virtual ~Resource();

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;

    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setPublisher(const string& publisher);
    void setTotalCopies(int totalCopies);

    bool isAvailable() const;
    bool borrow();
    bool returnBook();

    virtual string getType() const = 0;
    virtual string getInfo() const = 0;
    virtual void display() const = 0;
    virtual void displayBrief() const = 0;
    virtual string serialize() const = 0;
};

#endif
