#ifndef LIBRARY_H
#define LIBRARY_H

#include "User.h"
#include "Book.h"
#include "Magazine.h"
#include "ElectronicResource.h"
#include "BorrowRecord.h"
#include "Fine.h"
#include <vector>
#include <string>

class Library {
private:
    vector<User*> users;
    vector<Resource*> resources;
    vector<BorrowRecord> records;
    vector<Fine> fines;
    int nextUserId;
    int nextResourceId;
    int nextRecordId;
    int nextFineId;

public:
    Library();
    ~Library();

    // ==================== 用户管理 ====================
    bool addUser(const string& username, const string& name,
                 const string& userType, int maxBorrow = 0);
    bool deleteUser(int userId);
    User* findUser(int userId);
    User* findUserByUsername(const string& username);
    void listUsers() const;
    int getUserCount() const;

    // ==================== 资源管理 ====================
    bool addBook(const string& isbn, const string& title,
                 const string& author, const string& publisher,
                 int totalCopies = 1);
    bool addMagazine(const string& isbn, const string& title,
                     const string& author, const string& publisher,
                     const string& issueNumber, const string& publishMonth,
                     int totalCopies = 1);
    bool addElectronicResource(const string& isbn, const string& title,
                               const string& author, const string& publisher,
                               const string& fileFormat, double fileSizeMB,
                               const string& url, int totalCopies = 1);
    bool deleteResource(int resourceId);
    Resource* findResource(int resourceId);
    void listResources() const;
    void listBooks() const;
    void listMagazines() const;
    void listElectronicResources() const;
    int getResourceCount() const;

    // ==================== 借阅管理 ====================
    bool borrowBook(int userId, int resourceId);
    bool returnBook(int recordId);
    void listRecords() const;
    void listUserRecords(int userId) const;
    int getRecordCount() const;

    // ==================== 罚款管理 ====================
    void checkOverdue();
    bool payFine(int fineId);
    void listFines() const;
    void listUnpaidFines() const;
    int getFineCount() const;
    double getTotalUnpaidAmount() const;

    // ==================== 统计 ====================
    int getBorrowedCount() const;
    int getOverdueCount() const;
    int getStudentCount() const;
    int getTeacherCount() const;

    // ==================== 文件读写 ====================
    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);

    // ==================== 初始化示例数据 ====================
    void initSampleData();

    // ==================== 日期 ====================
    static string getCurrentDate();
    static string addDays(const string& date, int days);
};

#endif
