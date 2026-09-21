#include "Fine.h"

Fine::Fine()
    : id(0), userId(0), borrowRecordId(0), amount(0),
      reason(""), createdAt(""), paid(false) {
}

Fine::Fine(int id, int userId, int borrowRecordId, double amount,
           const string& reason, const string& createdAt)
    : id(id), userId(userId), borrowRecordId(borrowRecordId),
      amount(amount), reason(reason), createdAt(createdAt), paid(false) {
}

Fine::~Fine() {}

int Fine::getId() const { return id; }
int Fine::getUserId() const { return userId; }
int Fine::getBorrowRecordId() const { return borrowRecordId; }
double Fine::getAmount() const { return amount; }
string Fine::getReason() const { return reason; }
string Fine::getCreatedAt() const { return createdAt; }
bool Fine::isPaid() const { return paid; }

void Fine::setPaid(bool paid) { this->paid = paid; }
void Fine::setAmount(double amount) { if (isValidAmount(amount)) this->amount = amount; }
void Fine::setReason(const string& reason) { this->reason = reason; }

void Fine::display() const {
    cout << "罚款ID: " << id
         << " | 用户ID: " << userId
         << " | 借阅记录ID: " << borrowRecordId
         << " | 金额: " << amount << " 元"
         << " | 原因: " << reason
         << " | 日期: " << createdAt
         << " | 状态: " << (paid ? "已支付" : "未支付")
         << endl;
}

bool Fine::isValidAmount(double amount) {
    return amount > 0;
}
