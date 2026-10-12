#include "Library.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) throw runtime_error("输入结束");
        try {
            size_t used = 0;
            int value = stoi(line, &used);
            if (line.find_first_not_of(" \t\r", used) == string::npos) return value;
        } catch (const exception&) {}
        cout << "请输入有效整数。" << endl;
    }
}

string readText(const string& prompt) {
    while (true) {
        cout << prompt;
        string value;
        if (!getline(cin, value)) throw runtime_error("输入结束");
        if (value.find_first_not_of(" \t\r") != string::npos) return value;
        cout << "内容不能为空。" << endl;
    }
}

void addResource(Library& lib) {
    int type = readInt("资源类型：1 普通图书，2 杂志，3 电子资源：");
    if (type < 1 || type > 3) { cout << "资源类型无效。" << endl; return; }
    string title = readText("名称：");
    int copies = readInt("总数量（电子资源为并发授权数，必须大于0）：");
    if (copies <= 0) { cout << "数量必须大于0。" << endl; return; }
    if (type == 1) {
        string isbn = readText("ISBN：");
        string author = readText("作者：");
        string publisher = readText("出版社：");
        lib.addBook(isbn, title, author, publisher, copies);
    } else if (type == 2) {
        string issn = readText("ISSN：");
        string issue = readText("期号：");
        string publisher = readText("出版社：");
        lib.addMagazine(title, issn, issue, publisher, copies);
    } else {
        string url = readText("访问地址：");
        string format = readText("文件格式：");
        lib.addElectronicResource(title, url, format, copies);
    }
}

void runDemo() {
    Library lib;
    lib.addUser("s001", "张三", 5);
    lib.addBook("978-7-111-42190-5", "C++程序设计", "Bjarne", "机械工业出版社", 3);
    lib.addMagazine("计算机学报", "0254-4164", "2026年第10期", "科学出版社", 2);
    lib.addElectronicResource("C++电子教程", "https://example.com/cpp", "PDF", 2);
    cout << "\n===== 三种派生资源的不同信息 =====" << endl;
    lib.listResources();
    for (int id = 1; id <= 3; ++id) lib.borrowResource(1, id);
    lib.listRecords();
    lib.changeResourceCopies(1, 2);
    lib.changeResourceCopies(2, -1);
    lib.removeResource(3);
    for (int id = 1; id <= 3; ++id) lib.returnBook(id);
    lib.removeResource(3);
    lib.listResources();
    lib.listRecords();
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    if (argc > 1 && string(argv[1]) == "--demo") { runDemo(); return 0; }
    Library lib;
    cout << "===== 实验三：图书资源借阅管理系统 =====" << endl;
    try {
        while (true) {
            cout << "\n1 添加用户    2 查看用户    3 添加资源\n"
                 << "4 查看单个资源    5 查看所有资源\n"
                 << "6 增加数量    7 减少数量    8 删除资源\n"
                 << "9 借阅资源    10 归还资源    11 查看借阅记录\n"
                 << "0 退出\n";
            int choice = readInt("请选择：");
            switch (choice) {
            case 0: return 0;
            case 1: {
                string username = readText("学号/用户名：");
                string name = readText("姓名：");
                int limit = readInt("最大借阅数量（大于0）：");
                if (limit > 0) lib.addUser(username, name, limit);
                else cout << "借阅上限必须大于0。" << endl;
                break;
            }
            case 2: lib.listUsers(); break;
            case 3: addResource(lib); break;
            case 4: lib.displayResource(readInt("资源ID：")); break;
            case 5: lib.listResources(); break;
            case 6:
            case 7: {
                int id = readInt("资源ID：");
                int count = readInt("变更数量（大于0）：");
                if (count > 0) lib.changeResourceCopies(id, choice == 6 ? count : -count);
                else cout << "数量必须大于0。" << endl;
                break;
            }
            case 8: lib.removeResource(readInt("资源ID：")); break;
            case 9: {
                int userId = readInt("用户ID：");
                int resourceId = readInt("资源ID：");
                lib.borrowResource(userId, resourceId);
                break;
            }
            case 10: lib.returnBook(readInt("借阅记录ID：")); break;
            case 11: lib.listRecords(); break;
            default: cout << "没有这个选项。" << endl;
            }
        }
    } catch (const runtime_error&) {
        cout << "\n输入结束，程序退出。" << endl;
    }
    return 0;
}
