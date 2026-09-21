#ifndef FINE_H
#define FINE_H

#include <string>
#include <iostream>
using namespace std;

class Fine {
private:
    int id;
    int userId;
    int borrowRecordId;
    double amount;
    string reason;
    string createdAt;
    bool paid;

public:
    Fine();
    Fine(int id, int userId, int borrowRecordId, double amount,
         const string& reason, const string& createdAt);
    ~Fine();

    int getId() const;
    int getUserId() const;
    int getBorrowRecordId() const;
    double getAmount() const;
    string getReason() const;
    string getCreatedAt() const;
    bool isPaid() const;

    void setPaid(bool paid);
    void setAmount(double amount);
    void setReason(const string& reason);

    void display() const;

    static bool isValidAmount(double amount);
};

#endif
