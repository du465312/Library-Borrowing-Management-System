# 图书馆借阅管理系统

一个基于Flask的图书馆借阅管理系统，支持用户管理、图书管理、借阅管理和罚款管理功能。

## 功能特性

### 用户管理
- 支持学生和教师两种用户类型
- 用户信息的增删改查
- 用户类型区分借阅权限

### 图书管理
- 图书信息的增删改查
- 图书库存管理（总数量、可借数量）
- 图书分类管理

### 借阅管理
- 在线借阅图书
- 自动计算到期日期（教师30天，学生14天）
- 图书归还处理
- 借阅记录查询

### 罚款管理
- 逾期自动计算罚款（每天0.5元）
- 罚款记录管理
- 罚款支付确认

### 其他功能
- 首页仪表盘显示关键统计数据
- 逾期图书提醒
- 响应式Web界面
- RESTful API接口

## 技术栈

- **后端**: Python Flask
- **数据库**: SQLite (可轻松迁移到MySQL/PostgreSQL)
- **ORM**: Flask-SQLAlchemy
- **前端**: Bootstrap 5 + Bootstrap Icons
- **模板引擎**: Jinja2

## 项目结构

```
Library-Borrowing-Management-System/
├── app.py                 # 主应用文件
├── requirements.txt       # 依赖包列表
├── README.md             # 项目说明文档
├── templates/            # HTML模板目录
│   ├── base.html         # 基础模板
│   ├── index.html        # 首页
│   ├── users.html        # 用户列表
│   ├── add_user.html     # 添加用户
│   ├── edit_user.html    # 编辑用户
│   ├── books.html        # 图书列表
│   ├── add_book.html     # 添加图书
│   ├── edit_book.html    # 编辑图书
│   ├── borrow.html       # 借阅管理
│   ├── records.html      # 借阅记录
│   └── fines.html        # 罚款管理
└── static/               # 静态文件目录
```

## 安装与运行

### 1. 安装依赖
```bash
pip install -r requirements.txt
```

### 2. 运行应用
```bash
python app.py
```

### 3. 访问系统
打开浏览器访问: http://localhost:5000

## 数据库初始化

应用首次运行时会自动创建数据库和示例数据：
- 3个示例用户（2个学生，1个教师）
- 3本示例图书

## API接口

- `GET /api/users` - 获取所有用户
- `GET /api/books` - 获取所有图书
- `GET /api/overdue` - 获取逾期记录

## 借阅规则

| 用户类型 | 借阅天数 | 逾期罚款 |
|---------|---------|---------|
| 学生    | 14天    | 0.5元/天 |
| 教师    | 30天    | 0.5元/天 |

## 开发说明

### 数据库模型
- **User**: 用户信息（学生/教师）
- **Book**: 图书信息
- **BorrowRecord**: 借阅记录
- **Fine**: 罚款记录

### 扩展建议
1. 添加用户认证和权限管理
2. 实现图书搜索和高级查询
3. 添加邮件/短信提醒功能
4. 实现图书预约功能
5. 添加数据统计和报表功能
6. 支持条形码扫描

## 许可证

MIT License