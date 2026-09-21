#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

Library::Library() : nextUserId(1), nextResourceId(1), nextRecordId(1), nextFineId(1) {
}

Library::~Library() {
    for (auto u : users) delete u;
    for (auto r : resources) delete r;
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

bool Library::addUser(const string& username, const string& name,
                      const string& userType, int maxBorrow) {
    if (findUserByUsername(username) != nullptr) {
        cout << "[错误] 用户名已存在: " << username << endl;
        return false;
    }

    User* newUser = nullptr;
    if (userType == "teacher") {
        int mb = (maxBorrow > 0) ? maxBorrow : 10;
        newUser = new Teacher(nextUserId++, username, name, mb);
    } else {
        int mb = (maxBorrow > 0) ? maxBorrow : 5;
        newUser = new Student(nextUserId++, username, name, mb);
    }

    users.push_back(newUser);
    cout << "[成功] 用户添加成功: " << name << " (" << newUser->getRole() << ")" << endl;
    return true;
}

bool Library::deleteUser(int userId) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getId() == userId) {
            cout << "[成功] 用户已删除: " << (*it)->getName() << endl;
            delete *it;
            users.erase(it);
            return true;
        }
    }
    cout << "[错误] 未找到用户 ID: " << userId << endl;
    return false;
}

User* Library::findUser(int userId) {
    for (auto& user : users) {
        if (user->getId() == userId) return user;
    }
    return nullptr;
}

User* Library::findUserByUsername(const string& username) {
    for (auto& user : users) {
        if (user->getUsername() == username) return user;
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
        user->display();
    }
    cout << "====================" << endl;
}

int Library::getUserCount() const { return users.size(); }

// ==================== 资源管理 ====================

bool Library::addBook(const string& isbn, const string& title,
                      const string& author, const string& publisher,
                      int totalCopies) {
    Book* book = new Book(nextResourceId++, isbn, title, author, publisher, totalCopies);
    resources.push_back(book);
    cout << "[成功] 图书添加成功: " << title << " (ID: " << book->getId() << ")" << endl;
    return true;
}

bool Library::addMagazine(const string& isbn, const string& title,
                          const string& author, const string& publisher,
                          const string& issueNumber, const string& publishMonth,
                          int totalCopies) {
    Magazine* mag = new Magazine(nextResourceId++, isbn, title, author, publisher,
                                  issueNumber, publishMonth, totalCopies);
    resources.push_back(mag);
    cout << "[成功] 杂志添加成功: " << title << " (ID: " << mag->getId() << ")" << endl;
    return true;
}

bool Library::addElectronicResource(const string& isbn, const string& title,
                                    const string& author, const string& publisher,
                                    const string& fileFormat, double fileSizeMB,
                                    const string& url, int totalCopies) {
    ElectronicResource* er = new ElectronicResource(nextResourceId++, isbn, title,
                                                     author, publisher, fileFormat,
                                                     fileSizeMB, url, totalCopies);
    resources.push_back(er);
    cout << "[成功] 电子资源添加成功: " << title << " (ID: " << er->getId() << ")" << endl;
    return true;
}

bool Library::deleteResource(int resourceId) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if ((*it)->getId() == resourceId) {
            for (const auto& record : records) {
                if (record.getBookId() == resourceId && !record.isReturned()) {
                    cout << "[错误] 该资源还有未归还的借阅记录，无法删除" << endl;
                    return false;
                }
            }
            cout << "[成功] 资源已删除: " << (*it)->getTitle() << endl;
            delete *it;
            resources.erase(it);
            return true;
        }
    }
    cout << "[错误] 未找到资源 ID: " << resourceId << endl;
    return false;
}

Resource* Library::findResource(int resourceId) {
    for (auto& res : resources) {
        if (res->getId() == resourceId) return res;
    }
    return nullptr;
}

void Library::listResources() const {
    if (resources.empty()) {
        cout << "暂无资源" << endl;
        return;
    }
    cout << "===== 全部资源列表 =====" << endl;
    for (const auto& res : resources) {
        res->display();
    }
    cout << "========================" << endl;
}

void Library::listBooks() const {
    bool found = false;
    cout << "===== 图书列表 =====" << endl;
    for (const auto& res : resources) {
        if (res->getType() == "图书") {
            res->display();
            found = true;
        }
    }
    if (!found) cout << "暂无图书" << endl;
    cout << "====================" << endl;
}

void Library::listMagazines() const {
    bool found = false;
    cout << "===== 杂志列表 =====" << endl;
    for (const auto& res : resources) {
        if (res->getType() == "杂志") {
            res->display();
            found = true;
        }
    }
    if (!found) cout << "暂无杂志" << endl;
    cout << "====================" << endl;
}

void Library::listElectronicResources() const {
    bool found = false;
    cout << "===== 电子资源列表 =====" << endl;
    for (const auto& res : resources) {
        if (res->getType() == "电子资源") {
            res->display();
            found = true;
        }
    }
    if (!found) cout << "暂无电子资源" << endl;
    cout << "========================" << endl;
}

int Library::getResourceCount() const { return resources.size(); }

// ==================== 借阅管理 ====================

bool Library::borrowBook(int userId, int resourceId) {
    User* user = findUser(userId);
    if (user == nullptr) {
        cout << "[错误] 未找到用户 ID: " << userId << endl;
        return false;
    }

    Resource* resource = findResource(resourceId);
    if (resource == nullptr) {
        cout << "[错误] 未找到资源 ID: " << resourceId << endl;
        return false;
    }

    if (!resource->isAvailable()) {
        cout << "[错误] 该资源已全部借出" << endl;
        return false;
    }

    int userBorrowCount = 0;
    for (const auto& record : records) {
        if (record.getUserId() == userId && !record.isReturned()) {
            userBorrowCount++;
        }
    }
    if (userBorrowCount >= user->getMaxBorrow()) {
        cout << "[错误] 用户借阅数量已达上限 (" << user->getMaxBorrow() << " 本)" << endl;
        return false;
    }

    string today = getCurrentDate();
    string dueDate = addDays(today, user->getBorrowDays());

    BorrowRecord newRecord(nextRecordId++, userId, resourceId, today, dueDate);
    records.push_back(newRecord);

    resource->borrow();

    cout << "[成功] 借阅成功！" << endl;
    cout << "  用户: " << user->getName() << " (" << user->getRole() << ")" << endl;
    cout << "  资源: " << resource->getTitle() << " [" << resource->getType() << "]" << endl;
    cout << "  借阅日期: " << today << endl;
    cout << "  应还日期: " << dueDate << " (可借 " << user->getBorrowDays() << " 天)" << endl;
    return true;
}

bool Library::returnBook(int recordId) {
    for (auto& record : records) {
        if (record.getId() == recordId) {
            if (record.isReturned()) {
                cout << "[错误] 该记录已归还" << endl;
                return false;
            }

            string today = getCurrentDate();
            record.setReturnDate(today);

            Resource* resource = findResource(record.getBookId());
            if (resource) {
                resource->returnBook();
            }

            string dueDate = record.getDueDate();
            if (today > dueDate) {
                int overdueDays = BorrowRecord::calculateOverdueDays(dueDate, today);
                double fineAmount = overdueDays * 0.5;

                Fine fine(nextFineId++, record.getUserId(), record.getId(),
                          fineAmount, "逾期" + to_string(overdueDays) + "天", today);
                fines.push_back(fine);

                record.setStatus("overdue");
                record.setFineAmount(fineAmount);

                cout << "[注意] 归还成功，但已逾期 " << overdueDays << " 天" << endl;
                cout << "  罚款金额: " << fineAmount << " 元" << endl;
            } else {
                record.setStatus("returned");
                cout << "[成功] 归还成功！" << endl;
            }
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

void Library::listUserRecords(int userId) const {
    User* user = const_cast<Library*>(this)->findUser(userId);
    if (user == nullptr) {
        cout << "[错误] 未找到用户 ID: " << userId << endl;
        return;
    }
    cout << "===== " << user->getName() << " 的借阅记录 =====" << endl;
    bool found = false;
    for (const auto& record : records) {
        if (record.getUserId() == userId) {
            record.display();
            found = true;
        }
    }
    if (!found) cout << "暂无借阅记录" << endl;
    cout << "=====================================" << endl;
}

int Library::getRecordCount() const { return records.size(); }

// ==================== 罚款管理 ====================

void Library::checkOverdue() {
    string today = getCurrentDate();
    for (auto& record : records) {
        if (!record.isReturned() && !record.isOverdue()) {
            if (today > record.getDueDate()) {
                int overdueDays = BorrowRecord::calculateOverdueDays(record.getDueDate(), today);
                double fineAmount = overdueDays * 0.5;

                Fine fine(nextFineId++, record.getUserId(), record.getId(),
                          fineAmount, "逾期" + to_string(overdueDays) + "天", today);
                fines.push_back(fine);

                record.setStatus("overdue");
                record.setFineAmount(fineAmount);

                cout << "[逾期] 记录ID " << record.getId() << " 已逾期 "
                     << overdueDays << " 天，罚款 " << fineAmount << " 元" << endl;
            }
        }
    }
}

bool Library::payFine(int fineId) {
    for (auto& fine : fines) {
        if (fine.getId() == fineId) {
            if (fine.isPaid()) {
                cout << "[提示] 该罚款已支付" << endl;
                return false;
            }
            fine.setPaid(true);
            cout << "[成功] 罚款已支付: " << fine.getAmount() << " 元" << endl;
            return true;
        }
    }
    cout << "[错误] 未找到罚款 ID: " << fineId << endl;
    return false;
}

void Library::listFines() const {
    if (fines.empty()) {
        cout << "暂无罚款记录" << endl;
        return;
    }
    cout << "===== 罚款记录 =====" << endl;
    for (const auto& fine : fines) {
        fine.display();
    }
    cout << "====================" << endl;
}

void Library::listUnpaidFines() const {
    bool found = false;
    cout << "===== 未支付罚款 =====" << endl;
    for (const auto& fine : fines) {
        if (!fine.isPaid()) {
            fine.display();
            found = true;
        }
    }
    if (!found) cout << "暂无未支付罚款" << endl;
    cout << "====================" << endl;
}

int Library::getFineCount() const { return fines.size(); }

double Library::getTotalUnpaidAmount() const {
    double total = 0;
    for (const auto& fine : fines) {
        if (!fine.isPaid()) total += fine.getAmount();
    }
    return total;
}

// ==================== 统计 ====================

int Library::getBorrowedCount() const {
    int count = 0;
    for (const auto& record : records) {
        if (!record.isReturned()) count++;
    }
    return count;
}

int Library::getOverdueCount() const {
    int count = 0;
    for (const auto& record : records) {
        if (record.isOverdue()) count++;
    }
    return count;
}

int Library::getStudentCount() const {
    int count = 0;
    for (const auto& user : users) {
        if (user->getUserType() == "student") count++;
    }
    return count;
}

int Library::getTeacherCount() const {
    int count = 0;
    for (const auto& user : users) {
        if (user->getUserType() == "teacher") count++;
    }
    return count;
}

// ==================== 文件读写 ====================

bool Library::saveToFile(const string& filename) const {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cout << "[错误] 无法打开文件进行写入: " << filename << endl;
        return false;
    }

    // 保存用户
    for (const auto& user : users) {
        ofs << "USER|" << user->getId() << "|" << user->getUsername() << "|"
            << user->getName() << "|" << user->getUserType() << "|"
            << user->getMaxBorrow() << endl;
    }

    // 保存资源
    for (const auto& res : resources) {
        ofs << res->serialize() << endl;
    }

    // 保存借阅记录
    for (const auto& record : records) {
        ofs << "RECORD|" << record.getId() << "|" << record.getUserId() << "|"
            << record.getBookId() << "|" << record.getBorrowDate() << "|"
            << record.getDueDate() << "|" << record.getReturnDate() << "|"
            << record.getStatus() << "|" << record.getFineAmount() << endl;
    }

    // 保存罚款
    for (const auto& fine : fines) {
        ofs << "FINE|" << fine.getId() << "|" << fine.getUserId() << "|"
            << fine.getBorrowRecordId() << "|" << fine.getAmount() << "|"
            << fine.getReason() << "|" << fine.getCreatedAt() << "|"
            << (fine.isPaid() ? "1" : "0") << endl;
    }

    ofs.close();
    cout << "[成功] 数据已保存到 " << filename << endl;
    return true;
}

bool Library::loadFromFile(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "[错误] 无法打开文件进行读取: " << filename << endl;
        return false;
    }

    // 清空现有数据
    for (auto u : users) delete u;
    for (auto r : resources) delete r;
    users.clear();
    resources.clear();
    records.clear();
    fines.clear();

    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string type;
        getline(iss, type, '|');

        if (type == "USER") {
            int id; string username, name, userType; int maxBorrow;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, username, '|');
            getline(iss, name, '|');
            getline(iss, userType, '|');
            getline(iss, token, '|'); maxBorrow = stoi(token);

            User* user = nullptr;
            if (userType == "teacher") {
                user = new Teacher(id, username, name, maxBorrow);
            } else {
                user = new Student(id, username, name, maxBorrow);
            }
            users.push_back(user);
            if (id >= nextUserId) nextUserId = id + 1;

        } else if (type == "BOOK") {
            int id; string isbn, title, author, publisher; int total, avail;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, isbn, '|');
            getline(iss, title, '|');
            getline(iss, author, '|');
            getline(iss, publisher, '|');
            getline(iss, token, '|'); total = stoi(token);
            getline(iss, token, '|'); avail = stoi(token);

            Book* book = new Book(id, isbn, title, author, publisher, total);
            book->setTotalCopies(avail + (total - total));
            // 修正 availableCopies（setTotalCopies 会调整，所以先设为 total 再减去借出的）
            // 直接通过 available 调整
            while (book->getAvailableCopies() > avail) book->borrow();
            resources.push_back(book);
            if (id >= nextResourceId) nextResourceId = id + 1;

        } else if (type == "MAGAZINE") {
            int id; string isbn, title, author, publisher, issue, month; int total, avail;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, isbn, '|');
            getline(iss, title, '|');
            getline(iss, author, '|');
            getline(iss, publisher, '|');
            getline(iss, issue, '|');
            getline(iss, month, '|');
            getline(iss, token, '|'); total = stoi(token);
            getline(iss, token, '|'); avail = stoi(token);

            Magazine* mag = new Magazine(id, isbn, title, author, publisher, issue, month, total);
            while (mag->getAvailableCopies() > avail) mag->borrow();
            resources.push_back(mag);
            if (id >= nextResourceId) nextResourceId = id + 1;

        } else if (type == "ELECTRONIC") {
            int id; string isbn, title, author, publisher, format, url; double size; int total, avail;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, isbn, '|');
            getline(iss, title, '|');
            getline(iss, author, '|');
            getline(iss, publisher, '|');
            getline(iss, format, '|');
            getline(iss, token, '|'); size = stod(token);
            getline(iss, url, '|');
            getline(iss, token, '|'); total = stoi(token);
            getline(iss, token, '|'); avail = stoi(token);

            ElectronicResource* er = new ElectronicResource(id, isbn, title, author,
                                                             publisher, format, size, url, total);
            while (er->getAvailableCopies() > avail) er->borrow();
            resources.push_back(er);
            if (id >= nextResourceId) nextResourceId = id + 1;

        } else if (type == "RECORD") {
            int id, userId, bookId; string borrowDate, dueDate, returnDate, status; double fine;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, token, '|'); userId = stoi(token);
            getline(iss, token, '|'); bookId = stoi(token);
            getline(iss, borrowDate, '|');
            getline(iss, dueDate, '|');
            getline(iss, returnDate, '|');
            getline(iss, status, '|');
            getline(iss, token, '|'); fine = stod(token);

            BorrowRecord record(id, userId, bookId, borrowDate, dueDate);
            if (!returnDate.empty()) record.setReturnDate(returnDate);
            record.setStatus(status);
            record.setFineAmount(fine);
            records.push_back(record);
            if (id >= nextRecordId) nextRecordId = id + 1;

        } else if (type == "FINE") {
            int id, userId, recordId; double amount; string reason, createdAt; string paidStr;
            string token;
            getline(iss, token, '|'); id = stoi(token);
            getline(iss, token, '|'); userId = stoi(token);
            getline(iss, token, '|'); recordId = stoi(token);
            getline(iss, token, '|'); amount = stod(token);
            getline(iss, reason, '|');
            getline(iss, createdAt, '|');
            getline(iss, paidStr, '|');

            Fine fine(id, userId, recordId, amount, reason, createdAt);
            if (paidStr == "1") fine.setPaid(true);
            fines.push_back(fine);
            if (id >= nextFineId) nextFineId = id + 1;
        }
    }

    ifs.close();
    cout << "[成功] 数据已从 " << filename << " 加载" << endl;
    cout << "  用户: " << getUserCount() << " | 资源: " << getResourceCount()
         << " | 借阅记录: " << getRecordCount() << " | 罚款: " << getFineCount() << endl;
    return true;
}

// ==================== 初始化示例数据 ====================

void Library::initSampleData() {
    cout << "[初始化] 正在创建示例数据..." << endl;

    addUser("s001", "张三", "student", 5);
    addUser("s002", "李四", "student", 5);
    addUser("t001", "王老师", "teacher", 10);

    addBook("978-7-111-42190-5", "Python编程：从入门到实践", "Eric Matthes", "机械工业出版社", 5);
    addBook("978-7-115-41730-5", "深入理解计算机系统", "Randal E. Bryant", "人民邮电出版社", 3);
    addBook("978-7-302-46180-4", "数据结构（C语言版）", "严蔚敏", "清华大学出版社", 4);

    addMagazine("978-7-111-40000-0", "计算机研究与发展", "中国科学院", "科学出版社", "2024-01", "2024-01", 2);
    addElectronicResource("978-7-115-50000-0", "C++ Primer Plus 全套课件", "Stephen Prata", "人民邮电出版社",
                          "PDF", 128.5, "https://example.com/cpp-primer", 10);

    cout << "[初始化] 示例数据创建完成！" << endl;
    cout << "  用户: " << getUserCount() << " (学生:" << getStudentCount()
         << " 教师:" << getTeacherCount() << ")" << endl;
    cout << "  资源: " << getResourceCount() << endl;
}
