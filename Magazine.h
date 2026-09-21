#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Resource.h"

class Magazine : public Resource {
private:
    string isbn;
    string issueNumber;
    string publishMonth;

public:
    Magazine();
    Magazine(int id, const string& isbn, const string& title,
             const string& author, const string& publisher,
             const string& issueNumber, const string& publishMonth,
             int totalCopies);
    ~Magazine();

    string getIsbn() const;
    string getIssueNumber() const;
    string getPublishMonth() const;

    void setIsbn(const string& isbn);
    void setIssueNumber(const string& issueNumber);
    void setPublishMonth(const string& publishMonth);

    string getType() const override;
    string getInfo() const override;
    void display() const override;
    void displayBrief() const override;
    string serialize() const override;

    static bool isValidIsbn(const string& isbn);
};

#endif
