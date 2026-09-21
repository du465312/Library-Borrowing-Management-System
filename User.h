#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
protected:
    int id;
    string username;
    string name;
    string userType;
    int maxBorrow;

public:
    User();
    User(int id, const string& username, const string& name,
         const string& userType, int maxBorrow);
    virtual ~User();

    int getId() const;
    string getUsername() const;
    string getName() const;
    string getUserType() const;
    int getMaxBorrow() const;

    void setUsername(const string& username);
    void setName(const string& name);
    void setUserType(const string& userType);
    void setMaxBorrow(int maxBorrow);

    virtual string getRole() const = 0;
    virtual int getBorrowDays() const = 0;
    virtual void display() const;
    virtual void displayDetail() const;

    static bool isValidUserType(const string& type);
};

class Student : public User {
public:
    Student();
    Student(int id, const string& username, const string& name, int maxBorrow = 5);
    ~Student();

    string getRole() const override;
    int getBorrowDays() const override;
    void display() const override;
    void displayDetail() const override;
};

class Teacher : public User {
public:
    Teacher();
    Teacher(int id, const string& username, const string& name, int maxBorrow = 10);
    ~Teacher();

    string getRole() const override;
    int getBorrowDays() const override;
    void display() const override;
    void displayDetail() const override;
};

#endif
