#include "ElectronicResource.h"

ElectronicResource::ElectronicResource()
    : Resource(), isbn(""), fileFormat(""), fileSizeMB(0), url("") {
}

ElectronicResource::ElectronicResource(int id, const string& isbn, const string& title,
                                       const string& author, const string& publisher,
                                       const string& fileFormat, double fileSizeMB,
                                       const string& url, int totalCopies)
    : Resource(id, title, author, publisher, totalCopies),
      isbn(isbn), fileFormat(fileFormat), fileSizeMB(fileSizeMB), url(url) {
}

ElectronicResource::~ElectronicResource() {}

string ElectronicResource::getIsbn() const { return isbn; }
string ElectronicResource::getFileFormat() const { return fileFormat; }
double ElectronicResource::getFileSizeMB() const { return fileSizeMB; }
string ElectronicResource::getUrl() const { return url; }

void ElectronicResource::setIsbn(const string& isbn) { this->isbn = isbn; }
void ElectronicResource::setFileFormat(const string& fileFormat) { this->fileFormat = fileFormat; }
void ElectronicResource::setFileSizeMB(double fileSizeMB) { this->fileSizeMB = fileSizeMB; }
void ElectronicResource::setUrl(const string& url) { this->url = url; }

string ElectronicResource::getType() const { return "电子资源"; }

string ElectronicResource::getInfo() const {
    return "格式:" + fileFormat + " 大小:" + to_string(fileSizeMB) + "MB";
}

void ElectronicResource::display() const {
    cout << "ID: " << id
         << " | 类型: 电子资源"
         << " | ISBN: " << isbn
         << " | 资源名: " << title
         << " | 作者/上传者: " << author
         << " | 出版社/来源: " << publisher
         << " | 文件格式: " << fileFormat
         << " | 文件大小: " << fileSizeMB << "MB"
         << " | 链接: " << url
         << " | 库存: " << availableCopies << "/" << totalCopies
         << endl;
}

void ElectronicResource::displayBrief() const {
    cout << "[" << id << "] [电子资源] " << title << " (" << fileFormat << ")"
         << " (可借: " << availableCopies << ")" << endl;
}

string ElectronicResource::serialize() const {
    return "ELECTRONIC|" + to_string(id) + "|" + isbn + "|" + title + "|" +
           author + "|" + publisher + "|" + fileFormat + "|" +
           to_string(fileSizeMB) + "|" + url + "|" + to_string(totalCopies) + "|" +
           to_string(availableCopies);
}

bool ElectronicResource::isValidIsbn(const string& isbn) {
    return !isbn.empty() && isbn.length() >= 10;
}
