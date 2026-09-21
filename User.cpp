#include "User.h"

// ==================== User 基类 ====================

User::User() : id(0), username(""), name(""), userType("student"), maxBorrow(5) {
}

User::User(int id, const string& username, const string& name,
           const string& userType, int maxBorrow)
    : id(id), username(username), name(name) {
    if (isValidUserType(userType)) {
        this->userType = userType;
    } else {
        this->userType = "student";
    }
    this->maxBorrow = (maxBorrow > 0) ? maxBorrow : 5;
}

User::~User() {}

int User::getId() const { return id; }
string User::getUsername() const { return username; }
string User::getName() const { return name; }
string User::getUserType() const { return userType; }
int User::getMaxBorrow() const { return maxBorrow; }

void User::setUsername(const string& username) { this->username = username; }
void User::setName(const string& name) { this->name = name; }
void User::setMaxBorrow(int maxBorrow) {
    if (maxBorrow > 0) this->maxBorrow = maxBorrow;
}

void User::setUserType(const string& userType) {
    if (isValidUserType(userType)) {
        this->userType = userType;
    }
}

void User::display() const {
    cout << "ID: " << id
         << " | 用户名: " << username
         << " | 姓名: " << name
         << " | 类型: " << userType
         << " | 最大借阅: " << maxBorrow << " 本" << endl;
}

void User::displayDetail() const {
    display();
}

bool User::isValidUserType(const string& type) {
    return (type == "student" || type == "teacher");
}

// ==================== Student 子类 ====================

Student::Student() : User() {
    userType = "student";
    maxBorrow = 5;
}

Student::Student(int id, const string& username, const string& name, int maxBorrow)
    : User(id, username, name, "student", maxBorrow) {
}

Student::~Student() {}

string Student::getRole() const { return "学生"; }
int Student::getBorrowDays() const { return 14; }

void Student::display() const {
    cout << "ID: " << id
         << " | 用户名: " << username
         << " | 姓名: " << name
         << " | 类型: 学生"
         << " | 最大借阅: " << maxBorrow << " 本"
         << " | 借阅天数: " << getBorrowDays() << " 天" << endl;
}

void Student::displayDetail() const {
    cout << "===== 学生信息 =====" << endl;
    cout << "  ID: " << id << endl;
    cout << "  用户名: " << username << endl;
    cout << "  姓名: " << name << endl;
    cout << "  类型: 学生" << endl;
    cout << "  最大借阅: " << maxBorrow << " 本" << endl;
    cout << "  借阅天数: " << getBorrowDays() << " 天" << endl;
    cout << "====================" << endl;
}

// ==================== Teacher 子类 ====================

Teacher::Teacher() : User() {
    userType = "teacher";
    maxBorrow = 10;
}

Teacher::Teacher(int id, const string& username, const string& name, int maxBorrow)
    : User(id, username, name, "teacher", maxBorrow) {
}

Teacher::~Teacher() {}

string Teacher::getRole() const { return "教师"; }
int Teacher::getBorrowDays() const { return 30; }

void Teacher::display() const {
    cout << "ID: " << id
         << " | 用户名: " << username
         << " | 姓名: " << name
         << " | 类型: 教师"
         << " | 最大借阅: " << maxBorrow << " 本"
         << " | 借阅天数: " << getBorrowDays() << " 天" << endl;
}

void Teacher::displayDetail() const {
    cout << "===== 教师信息 =====" << endl;
    cout << "  ID: " << id << endl;
    cout << "  用户名: " << username << endl;
    cout << "  姓名: " << name << endl;
    cout << "  类型: 教师" << endl;
    cout << "  最大借阅: " << maxBorrow << " 本" << endl;
    cout << "  借阅天数: " << getBorrowDays() << " 天" << endl;
    cout << "====================" << endl;
}
