#include "Library.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <limits>
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
    if (totalCopies <= 0 || title.empty() || !Book::isValidIsbn(isbn)) {
        cout << "[错误] 名称、ISBN 或数量无效" << endl;
        return;
    }
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

void Library::addMagazine(const string& title, const string& issn, const string& issue,
                          const string& publisher, int totalCopies) {
    if (title.empty() || issn.empty() || issue.empty() || totalCopies <= 0) {
        cout << "[错误] 名称、ISSN、期号和数量不能为空或无效" << endl;
        return;
    }
    magazines.emplace_back(nextBookId++, title, issn, issue, publisher, totalCopies);
    cout << "[成功] 杂志添加成功: " << title << endl;
}

void Library::addElectronicResource(const string& title, const string& url,
                                    const string& format, int licenses) {
    if (title.empty() || url.empty() || format.empty() || licenses <= 0) {
        cout << "[错误] 名称、地址、格式和授权数量不能为空或无效" << endl;
        return;
    }
    electronicResources.emplace_back(nextBookId++, title, url, format, licenses);
    cout << "[成功] 电子资源添加成功: " << title << endl;
}

Resource* Library::findResource(int resourceId) {
    for (auto& book : books) if (book.getId() == resourceId) return &book;
    for (auto& magazine : magazines) if (magazine.getId() == resourceId) return &magazine;
    for (auto& resource : electronicResources)
        if (resource.getId() == resourceId) return &resource;
    return nullptr;
}

bool Library::displayResource(int resourceId) const {
    for (const auto& book : books)
        if (book.getId() == resourceId) { book.display(); return true; }
    for (const auto& magazine : magazines)
        if (magazine.getId() == resourceId) { magazine.display(); return true; }
    for (const auto& resource : electronicResources)
        if (resource.getId() == resourceId) { resource.display(); return true; }
    cout << "[错误] 资源不存在" << endl;
    return false;
}

void Library::listResources() const {
    if (getResourceCount() == 0) { cout << "暂无资源" << endl; return; }
    for (const auto& book : books) book.display();
    for (const auto& magazine : magazines) magazine.display();
    for (const auto& resource : electronicResources) resource.display();
}

int Library::getResourceCount() const {
    return books.size() + magazines.size() + electronicResources.size();
}

bool Library::changeResourceCopies(int resourceId, int change) {
    Resource* resource = findResource(resourceId);
    if (!resource) { cout << "[错误] 资源不存在" << endl; return false; }
    const long long total = static_cast<long long>(resource->getTotalCopies()) + change;
    if (total > numeric_limits<int>::max() || total < 0 ||
        !resource->setTotalCopies(static_cast<int>(total))) {
        cout << "[错误] 总量不能为负、溢出或小于已借出数量" << endl;
        return false;
    }
    cout << "[成功] 数量已更新" << endl;
    return true;
}

bool Library::removeResource(int resourceId) {
    Resource* resource = findResource(resourceId);
    if (!resource) { cout << "[错误] 资源不存在" << endl; return false; }
    if (resource->getAvailableCopies() != resource->getTotalCopies()) {
        cout << "[错误] 资源尚未全部归还，不能删除" << endl;
        return false;
    }
    books.erase(remove_if(books.begin(), books.end(), [resourceId](const Book& b) {
        return b.getId() == resourceId;
    }), books.end());
    magazines.erase(remove_if(magazines.begin(), magazines.end(), [resourceId](const Magazine& m) {
        return m.getId() == resourceId;
    }), magazines.end());
    electronicResources.erase(remove_if(electronicResources.begin(), electronicResources.end(),
        [resourceId](const ElectronicResource& r) { return r.getId() == resourceId; }),
        electronicResources.end());
    cout << "[成功] 资源已删除" << endl;
    return true;
}

// ==================== 借阅管理 ====================
// Library 依赖传入的 user 与 book 对象完成借阅操作。

bool Library::borrowBook(User& user, Book& book) {
    if (findUser(user.getId()) != &user || findBook(book.getId()) != &book) {
        cout << "[错误] 用户或图书不属于本馆" << endl;
        return false;
    }
    return borrowResource(user.getId(), book.getId());
}

bool Library::borrowResource(int userId, int resourceId) {
    User* user = findUser(userId);
    Resource* resource = findResource(resourceId);
    if (!user || !resource) {
        cout << "[错误] 用户或资源不存在" << endl;
        return false;
    }
    if (!resource->isAvailable()) {
        cout << "[错误] 该资源已全部借出" << endl;
        return false;
    }

    int borrowCount = 0;
    for (const auto& record : records) {
        if (record.getUserId() == user->getId() && !record.isReturned()) {
            borrowCount++;
        }
    }
    if (borrowCount >= user->getMaxBorrow()) {
        cout << "[错误] 用户借阅数量已达上限 (" << user->getMaxBorrow() << " 项)" << endl;
        return false;
    }

    string today = getCurrentDate();
    string dueDate = addDays(today, 14);
    records.push_back(BorrowRecord(nextRecordId++, user->getId(), resource->getId(), today, dueDate));
    resource->borrow();

    cout << "[成功] 借阅成功！" << endl;
    cout << "  用户: " << user->getName() << endl;
    cout << "  资源: " << resource->getTitle() << endl;
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
            Resource* resource = findResource(record.getBookId());
            if (!resource || !resource->returnBook()) {
                cout << "[错误] 资源不存在或库存状态异常" << endl;
                return false;
            }
            record.setReturnDate(getCurrentDate());
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
