from flask import Flask, render_template, request, redirect, url_for, flash, jsonify
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime, timedelta
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'library-secret-key'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///library.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

# 数据库模型
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    name = db.Column(db.String(100), nullable=False)
    user_type = db.Column(db.String(20), nullable=False)  # 'student' or 'teacher'
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    
    # 借阅记录关系
    borrow_records = db.relationship('BorrowRecord', backref='user', lazy=True)
    
    def __repr__(self):
        return f'<User {self.username}>'

class Book(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    isbn = db.Column(db.String(20), unique=True, nullable=False)
    title = db.Column(db.String(200), nullable=False)
    author = db.Column(db.String(100), nullable=False)
    publisher = db.Column(db.String(100))
    publish_date = db.Column(db.String(20))
    category = db.Column(db.String(50))
    total_copies = db.Column(db.Integer, default=1)
    available_copies = db.Column(db.Integer, default=1)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    
    # 借阅记录关系
    borrow_records = db.relationship('BorrowRecord', backref='book', lazy=True)
    
    def __repr__(self):
        return f'<Book {self.title}>'

class BorrowRecord(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)
    book_id = db.Column(db.Integer, db.ForeignKey('book.id'), nullable=False)
    borrow_date = db.Column(db.DateTime, default=datetime.utcnow, nullable=False)
    due_date = db.Column(db.DateTime, nullable=False)
    return_date = db.Column(db.DateTime)
    status = db.Column(db.String(20), default='borrowed')  # 'borrowed', 'returned', 'overdue'
    
    def __repr__(self):
        return f'<BorrowRecord {self.id}>'

class Fine(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)
    borrow_record_id = db.Column(db.Integer, db.ForeignKey('borrow_record.id'), nullable=False)
    amount = db.Column(db.Float, nullable=False)
    reason = db.Column(db.String(200))
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    paid = db.Column(db.Boolean, default=False)
    
    # 关系
    user = db.relationship('User', backref='fines')
    borrow_record = db.relationship('BorrowRecord', backref='fine')
    
    def __repr__(self):
        return f'<Fine {self.id}>'

# 路由
@app.route('/')
def index():
    from datetime import datetime
    users_count = User.query.count()
    books_count = Book.query.count()
    borrowed_count = BorrowRecord.query.filter_by(status='borrowed').count()
    overdue_count = BorrowRecord.query.filter(
        BorrowRecord.status == 'borrowed',
        BorrowRecord.due_date < datetime.utcnow()
    ).count()
    
    recent_records = BorrowRecord.query.order_by(BorrowRecord.borrow_date.desc()).limit(5).all()
    overdue_records = BorrowRecord.query.filter(
        BorrowRecord.status == 'borrowed',
        BorrowRecord.due_date < datetime.utcnow()
    ).all()
    
    return render_template('index.html', 
                         users_count=users_count,
                         books_count=books_count,
                         borrowed_count=borrowed_count,
                         overdue_count=overdue_count,
                         recent_records=recent_records,
                         overdue_records=overdue_records,
                         now=datetime.utcnow())

# 用户管理
@app.route('/users')
def users():
    users = User.query.all()
    return render_template('users.html', users=users)

@app.route('/users/add', methods=['GET', 'POST'])
def add_user():
    if request.method == 'POST':
        username = request.form['username']
        name = request.form['name']
        user_type = request.form['user_type']
        
        new_user = User(username=username, name=name, user_type=user_type)
        db.session.add(new_user)
        db.session.commit()
        
        flash('用户添加成功！', 'success')
        return redirect(url_for('users'))
    
    return render_template('add_user.html')

@app.route('/users/edit/<int:id>', methods=['GET', 'POST'])
def edit_user(id):
    user = User.query.get_or_404(id)
    
    if request.method == 'POST':
        user.username = request.form['username']
        user.name = request.form['name']
        user.user_type = request.form['user_type']
        
        db.session.commit()
        flash('用户信息更新成功！', 'success')
        return redirect(url_for('users'))
    
    return render_template('edit_user.html', user=user)

@app.route('/users/delete/<int:id>')
def delete_user(id):
    user = User.query.get_or_404(id)
    db.session.delete(user)
    db.session.commit()
    flash('用户已删除！', 'success')
    return redirect(url_for('users'))

# 图书管理
@app.route('/books')
def books():
    books = Book.query.all()
    return render_template('books.html', books=books)

@app.route('/books/add', methods=['GET', 'POST'])
def add_book():
    if request.method == 'POST':
        isbn = request.form['isbn']
        title = request.form['title']
        author = request.form['author']
        publisher = request.form['publisher']
        publish_date = request.form['publish_date']
        category = request.form['category']
        total_copies = int(request.form['total_copies'])
        
        new_book = Book(
            isbn=isbn,
            title=title,
            author=author,
            publisher=publisher,
            publish_date=publish_date,
            category=category,
            total_copies=total_copies,
            available_copies=total_copies
        )
        db.session.add(new_book)
        db.session.commit()
        
        flash('图书添加成功！', 'success')
        return redirect(url_for('books'))
    
    return render_template('add_book.html')

@app.route('/books/edit/<int:id>', methods=['GET', 'POST'])
def edit_book(id):
    book = Book.query.get_or_404(id)
    
    if request.method == 'POST':
        book.isbn = request.form['isbn']
        book.title = request.form['title']
        book.author = request.form['author']
        book.publisher = request.form['publisher']
        book.publish_date = request.form['publish_date']
        book.category = request.form['category']
        book.total_copies = int(request.form['total_copies'])
        # available_copies 根据借阅记录自动计算
        
        db.session.commit()
        flash('图书信息更新成功！', 'success')
        return redirect(url_for('books'))
    
    return render_template('edit_book.html', book=book)

@app.route('/books/delete/<int:id>')
def delete_book(id):
    book = Book.query.get_or_404(id)
    db.session.delete(book)
    db.session.commit()
    flash('图书已删除！', 'success')
    return redirect(url_for('books'))

# 借阅管理
@app.route('/borrow', methods=['GET', 'POST'])
def borrow():
    if request.method == 'POST':
        user_id = int(request.form['user_id'])
        book_id = int(request.form['book_id'])
        
        user = User.query.get_or_404(user_id)
        book = Book.query.get_or_404(book_id)
        
        if book.available_copies <= 0:
            flash('该图书已全部借出！', 'danger')
            return redirect(url_for('borrow'))
        
        # 计算到期日期（教师30天，学生14天）
        borrow_days = 30 if user.user_type == 'teacher' else 14
        due_date = datetime.utcnow() + timedelta(days=borrow_days)
        
        new_record = BorrowRecord(
            user_id=user_id,
            book_id=book_id,
            due_date=due_date,
            status='borrowed'
        )
        
        book.available_copies -= 1
        
        db.session.add(new_record)
        db.session.commit()
        
        flash(f'借阅成功！到期日期：{due_date.strftime("%Y-%m-%d")}', 'success')
        return redirect(url_for('borrow_records'))
    
    users = User.query.all()
    books = Book.query.filter(Book.available_copies > 0).all()
    return render_template('borrow.html', users=users, books=books)

@app.route('/return/<int:record_id>')
def return_book(record_id):
    record = BorrowRecord.query.get_or_404(record_id)
    
    if record.status == 'returned':
        flash('该图书已归还！', 'warning')
        return redirect(url_for('borrow_records'))
    
    record.return_date = datetime.utcnow()
    record.status = 'returned'
    
    # 更新图书可用数量
    book = Book.query.get(record.book_id)
    book.available_copies += 1
    
    # 检查是否逾期
    if datetime.utcnow() > record.due_date:
        overdue_days = (datetime.utcnow() - record.due_date).days
        fine_amount = overdue_days * 0.5  # 每天0.5元罚款
        
        fine = Fine(
            user_id=record.user_id,
            borrow_record_id=record.id,
            amount=fine_amount,
            reason=f'逾期{overdue_days}天',
            paid=False
        )
        db.session.add(fine)
        record.status = 'overdue'
        flash(f'归还成功，但已逾期{overdue_days}天，罚款{fine_amount}元', 'warning')
    else:
        flash('归还成功！', 'success')
    
    db.session.commit()
    return redirect(url_for('borrow_records'))

@app.route('/records')
def borrow_records():
    records = BorrowRecord.query.order_by(BorrowRecord.borrow_date.desc()).all()
    return render_template('records.html', records=records)

# 罚款管理
@app.route('/fines')
def fines():
    fines = Fine.query.order_by(Fine.created_at.desc()).all()
    
    # 计算统计数据
    unpaid_fines = Fine.query.filter_by(paid=False).all()
    paid_fines = Fine.query.filter_by(paid=True).all()
    
    unpaid_count = len(unpaid_fines)
    unpaid_amount = sum(f.amount for f in unpaid_fines)
    paid_amount = sum(f.amount for f in paid_fines)
    total_amount = unpaid_amount + paid_amount
    
    return render_template('fines.html', 
                         fines=fines,
                         unpaid_count=unpaid_count,
                         unpaid_amount=unpaid_amount,
                         paid_amount=paid_amount,
                         total_amount=total_amount)

@app.route('/fines/pay/<int:fine_id>')
def pay_fine(fine_id):
    fine = Fine.query.get_or_404(fine_id)
    fine.paid = True
    db.session.commit()
    flash('罚款已支付！', 'success')
    return redirect(url_for('fines'))

# API接口
@app.route('/api/users', methods=['GET'])
def api_users():
    users = User.query.all()
    return jsonify([{
        'id': u.id,
        'username': u.username,
        'name': u.name,
        'user_type': u.user_type
    } for u in users])

@app.route('/api/books', methods=['GET'])
def api_books():
    books = Book.query.all()
    return jsonify([{
        'id': b.id,
        'isbn': b.isbn,
        'title': b.title,
        'author': b.author,
        'available_copies': b.available_copies
    } for b in books])

@app.route('/api/overdue', methods=['GET'])
def api_overdue():
    records = BorrowRecord.query.filter(
        BorrowRecord.status == 'borrowed',
        BorrowRecord.due_date < datetime.utcnow()
    ).all()
    
    return jsonify([{
        'id': r.id,
        'user': r.user.name,
        'book': r.book.title,
        'due_date': r.due_date.strftime('%Y-%m-%d'),
        'overdue_days': (datetime.utcnow() - r.due_date).days
    } for r in records])

# 初始化数据库
def init_db():
    with app.app_context():
        db.create_all()
        
        # 添加示例数据
        if User.query.first() is None:
            # 示例用户
            users = [
                User(username='s001', name='张三', user_type='student'),
                User(username='s002', name='李四', user_type='student'),
                User(username='t001', name='王老师', user_type='teacher'),
            ]
            db.session.add_all(users)
            
            # 示例图书
            books = [
                Book(isbn='978-7-111-42190-5', title='Python编程：从入门到实践', author='Eric Matthes', publisher='机械工业出版社', publish_date='2016-07', category='计算机', total_copies=5, available_copies=5),
                Book(isbn='978-7-115-41730-5', title='深入理解计算机系统', author='Randal E. Bryant', publisher='人民邮电出版社', publish_date='2016-11', category='计算机', total_copies=3, available_copies=3),
                Book(isbn='978-7-302-46180-4', title='数据结构（C语言版）', author='严蔚敏', publisher='清华大学出版社', publish_date='2012-05', category='计算机', total_copies=4, available_copies=4),
            ]
            db.session.add_all(books)
            
            db.session.commit()

if __name__ == '__main__':
    init_db()
    app.run(debug=True, port=5000)