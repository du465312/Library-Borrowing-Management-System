#include "BorrowRecord.h"
#include <cstdlib>

BorrowRecord::BorrowRecord()
    : id(0), userId(0), bookId(0), borrowDate(""), dueDate(""),
      returnDate(""), status("borrowed"), fineAmount(0) {
}

BorrowRecord::BorrowRecord(int id, int userId, int bookId,
                           const string& borrowDate, const string& dueDate)
    : id(id), userId(userId), bookId(bookId),
      borrowDate(borrowDate), dueDate(dueDate),
      returnDate(""), status("borrowed"), fineAmount(0) {
}

BorrowRecord::~BorrowRecord() {}

int BorrowRecord::getId() const { return id; }
int BorrowRecord::getUserId() const { return userId; }
int BorrowRecord::getBookId() const { return bookId; }
string BorrowRecord::getBorrowDate() const { return borrowDate; }
string BorrowRecord::getDueDate() const { return dueDate; }
string BorrowRecord::getReturnDate() const { return returnDate; }
string BorrowRecord::getStatus() const { return status; }
double BorrowRecord::getFineAmount() const { return fineAmount; }

void BorrowRecord::setReturnDate(const string& returnDate) {
    this->returnDate = returnDate;
}

void BorrowRecord::setStatus(const string& status) {
    if (isValidStatus(status)) {
        this->status = status;
    }
}

void BorrowRecord::setFineAmount(double fineAmount) {
    this->fineAmount = fineAmount;
}

bool BorrowRecord::isReturned() const {
    return status == "returned";
}

bool BorrowRecord::isOverdue() const {
    return status == "overdue";
}

void BorrowRecord::display() const {
    string statusStr;
    if (status == "borrowed") statusStr = "借阅中";
    else if (status == "returned") statusStr = "已归还";
    else statusStr = "已逾期";

    cout << "记录ID: " << id
         << " | 用户ID: " << userId
         << " | 图书ID: " << bookId
         << " | 借阅日期: " << borrowDate
         << " | 应还日期: " << dueDate;
    if (!returnDate.empty()) {
        cout << " | 归还日期: " << returnDate;
    }
    cout << " | 状态: " << statusStr;
    if (fineAmount > 0) {
        cout << " | 罚款: " << fineAmount << "元";
    }
    cout << endl;
}

void BorrowRecord::displayDetailed() const {
    display();
}

bool BorrowRecord::isValidStatus(const string& status) {
    return (status == "borrowed" || status == "returned" || status == "overdue");
}

int BorrowRecord::calculateOverdueDays(const string& dueDate, const string& currentDate) {
    // 简单日期解析 YYYY-MM-DD
    int y1, m1, d1, y2, m2, d2;
    if (sscanf(dueDate.c_str(), "%d-%d-%d", &y1, &m1, &d1) != 3) return 0;
    if (sscanf(currentDate.c_str(), "%d-%d-%d", &y2, &m2, &d2) != 3) return 0;

    int days1 = y1 * 365 + m1 * 30 + d1;
    int days2 = y2 * 365 + m2 * 30 + d2;

    int diff = days2 - days1;
    return (diff > 0) ? diff : 0;
}
