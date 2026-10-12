#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource {
private:
    int id;
    string title;
    int totalCopies;
    int availableCopies;

public:
    Resource();
    Resource(int id, const string& title, int totalCopies);
    int getId() const;
    string getTitle() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;
    void setTitle(const string& title);
    bool setTotalCopies(int totalCopies);
    bool isAvailable() const;
    bool borrow();
    bool returnBook();
    void display() const;
};

#endif
