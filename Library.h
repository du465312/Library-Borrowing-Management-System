#ifndef LIBRARY_H
#define LIBRARY_H

#include "User.h"
#include "Book.h"
#include "BorrowRecord.h"
#include <vector>
#include <string>
using namespace std;

class Library {
private:
    // ==================== 组合关系 ====================
    // Library 由 User、Book、BorrowRecord 组成：
    // 这些对象作为成员随 Library 一起创建和销毁，属于“组合关系”(has-a)。
    vector<User> users;
    vector<Book> books;
    vector<BorrowRecord> records;

    int nextUserId;
    int nextBookId;
    int nextRecordId;

public:
    Library();

    // ==================== 用户管理 ====================
    void addUser(const string& username, const string& name, int maxBorrow = 5);
    User* findUser(int userId);
    void listUsers() const;
    int getUserCount() const;

    // ==================== 图书管理 ====================
    void addBook(const string& isbn, const string& title,
                 const string& author, const string& publisher,
                 int totalCopies = 1);
    Book* findBook(int bookId);
    void listBooks() const;
    int getBookCount() const;

    // ==================== 借阅管理 ====================
    // 依赖关系：以下方法通过参数接收 User、Book 对象，Library 在其实现中
    // 使用这两个类的功能，但二者并不是 Library 的成员，属于“依赖关系”(use-a)。
    bool borrowBook(User& user, Book& book);
    bool returnBook(int recordId);
    void listRecords() const;
    int getRecordCount() const;

    // ==================== 日期工具 ====================
    static string getCurrentDate();
    static string addDays(const string& date, int days);
};

#endif
