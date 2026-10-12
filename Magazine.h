#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Resource.h"

class Magazine : public Resource {
private:
    string issn;
    string issue;
    string publisher;
public:
    Magazine();
    Magazine(int id, const string& title, const string& issn,
             const string& issue, const string& publisher, int totalCopies);
    string getIssn() const;
    string getIssue() const;
    string getPublisher() const;
    void setIssue(const string& issue);
    void display() const;
};

#endif
