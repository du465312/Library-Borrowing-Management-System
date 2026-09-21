#include "Library.h"
#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

Library::Library() : nextUserId(1), nextBookId(1), nextRecordId(1) {
}

// ==================== 日期工具 ====================

string Library::getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(buf);
}

string Library::addDays(const string& date, int days) {
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3) return date;

    tm t = {};
    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d + days;
    mktime(&t);

    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", 1900 + t.tm_year, 1 + t.tm_mon, t.tm_mday);
    return string(buf);
}

// ==================== 用户管理 ====================

void Library::addUser(const string& username, const string& name, int maxBorrow) {
    users.push_back(User(nextUserId++, username, name, maxBorrow));
    cout << "[成功] 用户添加成功: " << name << endl;
}

User* Library::findUser(int userId) {
    for (auto& user : users) {
        if (user.getId() == userId) return &user;
    }
    return nullptr;
}

void Library::listUsers() const {
    if (users.empty()) {
        cout << "暂无用户" << endl;
        return;
    }
    cout << "===== 用户列表 =====" << endl;
    for (const auto& user : users) {
        user.display();
    }
    cout << "====================" << endl;
}

int Library::getUserCount() const { return users.size(); }

// ==================== 图书管理 ====================

void Library::addBook(const string& isbn, const string& title,
                      const string& author, const string& publisher,
                      int totalCopies) {
    books.push_back(Book(nextBookId++, isbn, title, author, publisher, totalCopies));
    cout << "[成功] 图书添加成功: " << title << endl;
}

Book* Library::findBook(int bookId) {
    for (auto& book : books) {
        if (book.getId() == bookId) return &book;
    }
    return nullptr;
}

void Library::listBooks() const {
    if (books.empty()) {
        cout << "暂无图书" << endl;
        return;
    }
    cout << "===== 图书列表 =====" << endl;
    for (const auto& book : books) {
        book.display();
    }
    cout << "====================" << endl;
}

int Library::getBookCount() const { return books.size(); }

// ==================== 借阅管理 ====================
// Library 依赖传入的 user 与 book 对象完成借阅操作。

bool Library::borrowBook(User& user, Book& book) {
    if (!book.isAvailable()) {
        cout << "[错误] 该图书已全部借出" << endl;
        return false;
    }

    int borrowCount = 0;
    for (const auto& record : records) {
        if (record.getUserId() == user.getId() && !record.isReturned()) {
            borrowCount++;
        }
    }
    if (borrowCount >= user.getMaxBorrow()) {
        cout << "[错误] 用户借阅数量已达上限 (" << user.getMaxBorrow() << " 本)" << endl;
        return false;
    }

    string today = getCurrentDate();
    string dueDate = addDays(today, 14);
    records.push_back(BorrowRecord(nextRecordId++, user.getId(), book.getId(), today, dueDate));
    book.borrow();

    cout << "[成功] 借阅成功！" << endl;
    cout << "  用户: " << user.getName() << endl;
    cout << "  图书: " << book.getTitle() << endl;
    cout << "  借阅日期: " << today << " | 应还日期: " << dueDate << endl;
    return true;
}

bool Library::returnBook(int recordId) {
    for (auto& record : records) {
        if (record.getId() == recordId) {
            if (record.isReturned()) {
                cout << "[错误] 该记录已归还" << endl;
                return false;
            }
            record.setReturnDate(getCurrentDate());

            Book* book = findBook(record.getBookId());
            if (book) {
                book->returnBook();
            }
            cout << "[成功] 归还成功！" << endl;
            return true;
        }
    }
    cout << "[错误] 未找到借阅记录 ID: " << recordId << endl;
    return false;
}

void Library::listRecords() const {
    if (records.empty()) {
        cout << "暂无借阅记录" << endl;
        return;
    }
    cout << "===== 借阅记录 =====" << endl;
    for (const auto& record : records) {
        record.display();
    }
    cout << "====================" << endl;
}

int Library::getRecordCount() const { return records.size(); }
