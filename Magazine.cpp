#include "Magazine.h"
#include <iostream>

Magazine::Magazine() : Resource() {}
Magazine::Magazine(int id, const string& title, const string& issn,
                   const string& issue, const string& publisher, int totalCopies)
    : Resource(id, title, totalCopies), issn(issn), issue(issue), publisher(publisher) {}
string Magazine::getIssn() const { return issn; }
string Magazine::getIssue() const { return issue; }
string Magazine::getPublisher() const { return publisher; }
void Magazine::setIssue(const string& issue) { this->issue = issue; }
void Magazine::display() const {
    cout << "[杂志] ";
    Resource::display();
    cout << " | ISSN: " << issn << " | 期号: " << issue
         << " | 出版社: " << publisher << endl;
}
