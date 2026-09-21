#include "BorrowRecord.h"

BorrowRecord::BorrowRecord()
    : id(0), userId(0), bookId(0), borrowDate(""), dueDate(""),
      returnDate(""), returned(false) {
}

BorrowRecord::BorrowRecord(int id, int userId, int bookId,
                           const string& borrowDate, const string& dueDate)
    : id(id), userId(userId), bookId(bookId),
      borrowDate(borrowDate), dueDate(dueDate),
      returnDate(""), returned(false) {
}

int BorrowRecord::getId() const { return id; }
int BorrowRecord::getUserId() const { return userId; }
int BorrowRecord::getBookId() const { return bookId; }
string BorrowRecord::getBorrowDate() const { return borrowDate; }
string BorrowRecord::getDueDate() const { return dueDate; }
string BorrowRecord::getReturnDate() const { return returnDate; }
bool BorrowRecord::isReturned() const { return returned; }

void BorrowRecord::setReturnDate(const string& returnDate) {
    this->returnDate = returnDate;
    this->returned = true;
}

void BorrowRecord::display() const {
    cout << "记录ID: " << id
         << " | 用户ID: " << userId
         << " | 图书ID: " << bookId
         << " | 借阅日期: " << borrowDate
         << " | 应还日期: " << dueDate;
    if (returned) {
        cout << " | 归还日期: " << returnDate;
    }
    cout << " | 状态: " << (returned ? "已归还" : "借阅中");
    cout << endl;
}
