#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>
#include <iostream>
using namespace std;

class BorrowRecord {
private:
    int id;
    int userId;
    int bookId;
    string borrowDate;
    string dueDate;
    string returnDate;
    string status;
    double fineAmount;

public:
    BorrowRecord();
    BorrowRecord(int id, int userId, int bookId,
                 const string& borrowDate, const string& dueDate);
    ~BorrowRecord();

    int getId() const;
    int getUserId() const;
    int getBookId() const;
    string getBorrowDate() const;
    string getDueDate() const;
    string getReturnDate() const;
    string getStatus() const;
    double getFineAmount() const;

    void setReturnDate(const string& returnDate);
    void setStatus(const string& status);
    void setFineAmount(double fineAmount);

    bool isReturned() const;
    bool isOverdue() const;

    void display() const;
    void displayDetailed() const;

    static bool isValidStatus(const string& status);
    static int calculateOverdueDays(const string& dueDate, const string& currentDate);
};

#endif
