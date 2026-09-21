#include "Magazine.h"

Magazine::Magazine()
    : Resource(), isbn(""), issueNumber(""), publishMonth("") {
}

Magazine::Magazine(int id, const string& isbn, const string& title,
                   const string& author, const string& publisher,
                   const string& issueNumber, const string& publishMonth,
                   int totalCopies)
    : Resource(id, title, author, publisher, totalCopies),
      isbn(isbn), issueNumber(issueNumber), publishMonth(publishMonth) {
}

Magazine::~Magazine() {}

string Magazine::getIsbn() const { return isbn; }
string Magazine::getIssueNumber() const { return issueNumber; }
string Magazine::getPublishMonth() const { return publishMonth; }

void Magazine::setIsbn(const string& isbn) { this->isbn = isbn; }
void Magazine::setIssueNumber(const string& issueNumber) { this->issueNumber = issueNumber; }
void Magazine::setPublishMonth(const string& publishMonth) { this->publishMonth = publishMonth; }

string Magazine::getType() const { return "杂志"; }

string Magazine::getInfo() const {
    return "期号:" + issueNumber + " 出版月份:" + publishMonth;
}

void Magazine::display() const {
    cout << "ID: " << id
         << " | 类型: 杂志"
         << " | ISBN: " << isbn
         << " | 期刊名: " << title
         << " | 作者/编者: " << author
         << " | 出版社: " << publisher
         << " | 期号: " << issueNumber
         << " | 出版月份: " << publishMonth
         << " | 库存: " << availableCopies << "/" << totalCopies
         << endl;
}

void Magazine::displayBrief() const {
    cout << "[" << id << "] [杂志] " << title << " 第" << issueNumber << "期"
         << " (可借: " << availableCopies << ")" << endl;
}

string Magazine::serialize() const {
    return "MAGAZINE|" + to_string(id) + "|" + isbn + "|" + title + "|" +
           author + "|" + publisher + "|" + issueNumber + "|" +
           publishMonth + "|" + to_string(totalCopies) + "|" +
           to_string(availableCopies);
}

bool Magazine::isValidIsbn(const string& isbn) {
    return !isbn.empty() && isbn.length() >= 10;
}
