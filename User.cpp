#include "User.h"

User::User() : id(0), username(""), name(""), maxBorrow(5) {
}

User::User(int id, const string& username, const string& name, int maxBorrow)
    : id(id), username(username), name(name) {
    this->maxBorrow = (maxBorrow > 0) ? maxBorrow : 5;
}

int User::getId() const { return id; }
string User::getUsername() const { return username; }
string User::getName() const { return name; }
int User::getMaxBorrow() const { return maxBorrow; }

void User::setName(const string& name) { this->name = name; }
void User::setMaxBorrow(int maxBorrow) {
    if (maxBorrow > 0) this->maxBorrow = maxBorrow;
}

void User::display() const {
    cout << "用户ID: " << id
         << " | 用户名: " << username
         << " | 姓名: " << name
         << " | 最大借阅: " << maxBorrow << " 本" << endl;
}
