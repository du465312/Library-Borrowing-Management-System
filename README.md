# 实验三 继承与派生

本项目在实验二的图书馆借阅程序上加入普通图书、杂志和电子资源，完成资源管理及借还操作。

## 类的结构

```text
Resource
  +-- Book
  +-- Magazine
  +-- ElectronicResource
```

三个子类均使用 `public` 继承。`Resource` 封装编号、名称、总量、可借数量，提供查询、修改数量、借阅和归还操作。派生类通过初始化列表调用基类构造函数；基类成员为 `private`，子类通过公有接口使用它们。

- `Book` 增加 ISBN、作者、出版社。
- `Magazine` 增加 ISSN、期号、出版社，并提供修改期号操作。
- `ElectronicResource` 增加访问地址和格式，并提供修改地址操作。数量表示可同时借阅的授权数。

各子类的 `display()` 显示自身信息，并显式调用 `Resource::display()` 输出公共信息。这是同名函数隐藏，尚未使用实验四的虚函数多态。`Library` 分别保存三个类型的对象，显示时通过具体类型调用函数；借还时通过 `Resource*` 调用继承的公共操作。基类指针只借用对象，不通过基类指针释放对象。

`User` 代表借阅用户，可用学号作为用户名；`BorrowRecord` 保存用户和资源编号。三种资源共用递增编号，删除后不重用编号，历史记录得以保留。

## 功能

菜单支持添加用户、查看用户、添加三种资源、查看单个或全部资源、增加或减少数量、删除资源、借阅、归还及查看借阅记录。

借阅检查用户、资源、库存及用户借阅上限。减少数量不能小于已借出数量；尚未归还的资源不能删除；重复归还不会改变库存。电子资源同样按授权数进行借还。

数据仅在当前运行中保存，文件存储属于后续实验六。现有 ISBN 验证仅检查非空及长度至少为 10，未实现 ISBN 校验码算法。

## 编译和运行

在项目目录使用支持 C++11 的编译器：

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 Resource.cpp Book.cpp Magazine.cpp ElectronicResource.cpp User.cpp BorrowRecord.cpp Library.cpp main.cpp -o library_app.exe
.\library_app.exe
```

运行完整演示，无需键盘输入：

```powershell
.\library_app.exe --demo
```

演示会添加三种资源、逐个借阅、修改数量、验证未归还不能删除，最后归还并删除电子资源。

Visual Studio 可直接打开此目录中的 CMake 项目，运行 `library_app`；也可以创建控制台项目并加入根目录所有 `.h` 和 `.cpp` 文件，设置源文件字符集为 UTF-8，排除 `tests` 中的测试入口。

安装了 CMake 的环境也可以执行：

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## 答辩时说明

说明为什么三种资源具有共同的基类，哪些成员被继承，哪些成员是子类特有；展示构造函数初始化列表、公共函数调用和同名函数隐藏。随后演示三类资源借还，以及库存不足、借阅上限、减少数量和删除资源的限制。
