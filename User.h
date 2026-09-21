#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

// 用户类（已删除 Student/Teacher 继承结构）
class User {
private:
    int id;
    string username;
    string name;
    int maxBorrow;

public:
    User();
    User(int id, const string& username, const string& name, int maxBorrow);

    int getId() const;
    string getUsername() const;
    string getName() const;
    int getMaxBorrow() const;

    void setName(const string& name);
    void setMaxBorrow(int maxBorrow);

    void display() const;
};

#endif
