#include "Library.h"
#include <iostream>
using namespace std;

int main() {
    Library lib;

    cout << "===== 类与对象：组合关系、依赖关系 示例 =====" << endl;
    cout << endl;

    // 【组合关系】User、Book 对象作为 Library 的成员被组合进来
    cout << "--- 演示组合关系：向 Library 加入 User / Book ---" << endl;
    lib.addUser("s001", "张三", 5);
    lib.addUser("t001", "王老师", 10);
    lib.addBook("978-7-111-42190-5", "C++程序设计", "Bjarne", "机械工业出版社", 3);
    lib.listUsers();
    lib.listBooks();
    cout << endl;

    // 【依赖关系】borrowBook 依赖传入的 User 和 Book 对象完成操作
    cout << "--- 演示依赖关系：borrowBook(User&, Book&) ---" << endl;
    User* user = lib.findUser(1);
    Book* book = lib.findBook(1);
    if (user != nullptr && book != nullptr) {
        lib.borrowBook(*user, *book);
    }
    lib.listRecords();
    cout << endl;

    // 归还
    cout << "--- 归还图书 ---" << endl;
    lib.returnBook(1);
    lib.listRecords();

    return 0;
}
