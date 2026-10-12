#ifndef LIBRARY_H
#define LIBRARY_H

#include "User.h"
#include "Book.h"
#include "Magazine.h"
#include "ElectronicResource.h"
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
    vector<Magazine> magazines;
    vector<ElectronicResource> electronicResources;
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

    void addMagazine(const string& title, const string& issn, const string& issue,
                     const string& publisher, int totalCopies = 1);
    void addElectronicResource(const string& title, const string& url,
                               const string& format, int licenses = 1);
    Resource* findResource(int resourceId);
    bool displayResource(int resourceId) const;
    void listResources() const;
    int getResourceCount() const;
    bool changeResourceCopies(int resourceId, int change);
    bool removeResource(int resourceId);

    // ==================== 借阅管理 ====================
    // 通过引用使用用户和资源；资源参数接受公有派生类对象。
    bool borrowBook(User& user, Book& book);
    bool borrowResource(int userId, int resourceId);
    bool returnBook(int recordId);
    void listRecords() const;
    int getRecordCount() const;

    // ==================== 日期工具 ====================
    static string getCurrentDate();
    static string addDays(const string& date, int days);
};

#endif
