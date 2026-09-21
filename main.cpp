#include "Library.h"
#include <iostream>
#include <string>
using namespace std;

void clearScreen() {
    system("cls");
}

void printMainMenu() {
    cout << endl;
    cout << "============================================" << endl;
    cout << "          图书馆借阅管理系统（C++版）        " << endl;
    cout << "============================================" << endl;
    cout << "  1. 用户管理（学生/教师）" << endl;
    cout << "  2. 资源管理（图书/杂志/电子资源）" << endl;
    cout << "  3. 借阅管理" << endl;
    cout << "  4. 罚款管理" << endl;
    cout << "  5. 系统统计" << endl;
    cout << "  6. 数据存盘" << endl;
    cout << "  7. 数据读取" << endl;
    cout << "  8. 加载示例数据" << endl;
    cout << "  0. 退出系统" << endl;
    cout << "============================================" << endl;
    cout << "请输入选项: ";
}

void userMenu(Library& lib) {
    int choice;
    do {
        cout << endl;
        cout << "======== 用户管理 ========" << endl;
        cout << "  1. 添加用户" << endl;
        cout << "  2. 查看用户列表" << endl;
        cout << "  3. 查看用户详情" << endl;
        cout << "  4. 修改用户" << endl;
        cout << "  5. 删除用户" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "==========================" << endl;
        cout << "请输入选项: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, name, userType;
                int maxBorrow;
                cout << "请输入用户名: ";
                cin >> username;
                cout << "请输入姓名: ";
                cin >> name;
                cout << "请输入类型 (student/teacher): ";
                cin >> userType;
                cout << "请输入最大借阅数 (0使用默认值): ";
                cin >> maxBorrow;
                lib.addUser(username, name, userType, maxBorrow);
                break;
            }
            case 2:
                lib.listUsers();
                break;
            case 3: {
                int userId;
                cout << "请输入用户ID: ";
                cin >> userId;
                User* user = lib.findUser(userId);
                if (user) {
                    user->displayDetail();
                } else {
                    cout << "[错误] 未找到用户" << endl;
                }
                break;
            }
            case 4: {
                int userId;
                cout << "请输入要修改的用户ID: ";
                cin >> userId;
                User* user = lib.findUser(userId);
                if (user) {
                    string name;
                    cout << "请输入新姓名 (回车跳过): ";
                    cin.ignore();
                    getline(cin, name);
                    if (!name.empty()) user->setName(name);

                    int maxBorrow;
                    cout << "请输入新最大借阅数 (0跳过): ";
                    cin >> maxBorrow;
                    if (maxBorrow > 0) user->setMaxBorrow(maxBorrow);

                    cout << "[成功] 用户信息已更新" << endl;
                    user->display();
                } else {
                    cout << "[错误] 未找到用户" << endl;
                }
                break;
            }
            case 5: {
                int userId;
                cout << "请输入要删除的用户ID: ";
                cin >> userId;
                lib.deleteUser(userId);
                break;
            }
            case 0:
                break;
            default:
                cout << "无效选项" << endl;
        }
    } while (choice != 0);
}

void resourceMenu(Library& lib) {
    int choice;
    do {
        cout << endl;
        cout << "======== 资源管理 ========" << endl;
        cout << "  1. 添加图书" << endl;
        cout << "  2. 添加杂志" << endl;
        cout << "  3. 添加电子资源" << endl;
        cout << "  4. 查看全部资源" << endl;
        cout << "  5. 按类型查看（图书）" << endl;
        cout << "  6. 按类型查看（杂志）" << endl;
        cout << "  7. 按类型查看（电子资源）" << endl;
        cout << "  8. 删除资源" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "==========================" << endl;
        cout << "请输入选项: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string isbn, title, author, publisher;
                int totalCopies;
                cout << "请输入ISBN: ";
                cin >> isbn;
                cout << "请输入书名: ";
                cin.ignore();
                getline(cin, title);
                cout << "请输入作者: ";
                getline(cin, author);
                cout << "请输入出版社: ";
                getline(cin, publisher);
                cout << "请输入总数量: ";
                cin >> totalCopies;
                lib.addBook(isbn, title, author, publisher, totalCopies);
                break;
            }
            case 2: {
                string isbn, title, author, publisher, issue, month;
                int totalCopies;
                cout << "请输入ISSN/ISBN: ";
                cin >> isbn;
                cout << "请输入期刊名: ";
                cin.ignore();
                getline(cin, title);
                cout << "请输入编者: ";
                getline(cin, author);
                cout << "请输入出版社: ";
                getline(cin, publisher);
                cout << "请输入期号: ";
                getline(cin, issue);
                cout << "请输入出版月份(如2024-01): ";
                getline(cin, month);
                cout << "请输入总数量: ";
                cin >> totalCopies;
                lib.addMagazine(isbn, title, author, publisher, issue, month, totalCopies);
                break;
            }
            case 3: {
                string isbn, title, author, publisher, format, url;
                double fileSize;
                int totalCopies;
                cout << "请输入ISBN: ";
                cin >> isbn;
                cout << "请输入资源名: ";
                cin.ignore();
                getline(cin, title);
                cout << "请输入作者/上传者: ";
                getline(cin, author);
                cout << "请输入来源: ";
                getline(cin, publisher);
                cout << "请输入文件格式(如PDF): ";
                getline(cin, format);
                cout << "请输入文件大小(MB): ";
                cin >> fileSize;
                cout << "请输入下载链接: ";
                cin.ignore();
                getline(cin, url);
                cout << "请输入副本数: ";
                cin >> totalCopies;
                lib.addElectronicResource(isbn, title, author, publisher, format, fileSize, url, totalCopies);
                break;
            }
            case 4:
                lib.listResources();
                break;
            case 5:
                lib.listBooks();
                break;
            case 6:
                lib.listMagazines();
                break;
            case 7:
                lib.listElectronicResources();
                break;
            case 8: {
                int resId;
                cout << "请输入要删除的资源ID: ";
                cin >> resId;
                lib.deleteResource(resId);
                break;
            }
            case 0:
                break;
            default:
                cout << "无效选项" << endl;
        }
    } while (choice != 0);
}

void borrowMenu(Library& lib) {
    int choice;
    do {
        cout << endl;
        cout << "======== 借阅管理 ========" << endl;
        cout << "  1. 借书" << endl;
        cout << "  2. 还书" << endl;
        cout << "  3. 查看所有借阅记录" << endl;
        cout << "  4. 查看某用户借阅记录" << endl;
        cout << "  5. 逾期检查" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "==========================" << endl;
        cout << "请输入选项: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "--- 可用用户 ---" << endl;
                lib.listUsers();
                cout << "--- 可用资源 ---" << endl;
                lib.listResources();
                int userId, resId;
                cout << "请输入用户ID: ";
                cin >> userId;
                cout << "请输入资源ID: ";
                cin >> resId;
                lib.borrowBook(userId, resId);
                break;
            }
            case 2: {
                cout << "--- 当前借阅记录 ---" << endl;
                lib.listRecords();
                int recordId;
                cout << "请输入要归还的记录ID: ";
                cin >> recordId;
                lib.returnBook(recordId);
                break;
            }
            case 3:
                lib.listRecords();
                break;
            case 4: {
                int userId;
                cout << "请输入用户ID: ";
                cin >> userId;
                lib.listUserRecords(userId);
                break;
            }
            case 5:
                lib.checkOverdue();
                cout << "[完成] 逾期检查完毕" << endl;
                break;
            case 0:
                break;
            default:
                cout << "无效选项" << endl;
        }
    } while (choice != 0);
}

void fineMenu(Library& lib) {
    int choice;
    do {
        cout << endl;
        cout << "======== 罚款管理 ========" << endl;
        cout << "  1. 查看所有罚款" << endl;
        cout << "  2. 查看未支付罚款" << endl;
        cout << "  3. 支付罚款" << endl;
        cout << "  4. 罚款统计" << endl;
        cout << "  0. 返回主菜单" << endl;
        cout << "==========================" << endl;
        cout << "请输入选项: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.listFines();
                break;
            case 2:
                lib.listUnpaidFines();
                break;
            case 3: {
                int fineId;
                cout << "请输入要支付的罚款ID: ";
                cin >> fineId;
                lib.payFine(fineId);
                break;
            }
            case 4:
                cout << "  罚款总数: " << lib.getFineCount() << endl;
                cout << "  未支付总额: " << lib.getTotalUnpaidAmount() << " 元" << endl;
                break;
            case 0:
                break;
            default:
                cout << "无效选项" << endl;
        }
    } while (choice != 0);
}

void statsMenu(const Library& lib) {
    cout << endl;
    cout << "============ 系统统计 ============" << endl;
    cout << "  用户总数: " << lib.getUserCount()
         << " (学生:" << lib.getStudentCount()
         << " 教师:" << lib.getTeacherCount() << ")" << endl;
    cout << "  资源总数: " << lib.getResourceCount() << endl;
    cout << "  借阅记录数: " << lib.getRecordCount() << endl;
    cout << "  当前借出: " << lib.getBorrowedCount() << endl;
    cout << "  逾期数量: " << lib.getOverdueCount() << endl;
    cout << "  罚款记录: " << lib.getFineCount() << endl;
    cout << "  未支付罚款: " << lib.getTotalUnpaidAmount() << " 元" << endl;
    cout << "===================================" << endl;
}

int main() {
    Library lib;
    int choice;

    cout << "欢迎使用图书馆借阅管理系统（C++版）！" << endl;
    cout << "提示：首次使用请先加载示例数据（选项8）" << endl;

    do {
        printMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                userMenu(lib);
                break;
            case 2:
                resourceMenu(lib);
                break;
            case 3:
                borrowMenu(lib);
                break;
            case 4:
                fineMenu(lib);
                break;
            case 5:
                statsMenu(lib);
                break;
            case 6: {
                string filename;
                cout << "请输入保存文件名: ";
                cin >> filename;
                lib.saveToFile(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "请输入读取文件名: ";
                cin >> filename;
                lib.loadFromFile(filename);
                break;
            }
            case 8:
                lib.initSampleData();
                break;
            case 0:
                cout << "感谢使用，再见！" << endl;
                break;
            default:
                cout << "无效选项，请重新输入" << endl;
        }
    } while (choice != 0);

    return 0;
}
