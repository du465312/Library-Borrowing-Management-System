#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>
#include <iostream>
using namespace std;

// 借阅记录类（已删除罚款/逾期相关字段）
class BorrowRecord {
private:
    int id;
    int userId;
    int bookId;
    string borrowDate;
    string dueDate;
    string returnDate;
    bool returned;

public:
    BorrowRecord();
    BorrowRecord(int id, int userId, int bookId,
                 const string& borrowDate, const string& dueDate);

    int getId() const;
    int getUserId() const;
    int getBookId() const;
    string getBorrowDate() const;
    string getDueDate() const;
    string getReturnDate() const;
    bool isReturned() const;

    void setReturnDate(const string& returnDate);

    void display() const;
};

#endif
