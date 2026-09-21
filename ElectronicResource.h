#ifndef ELECTRONICRESOURCE_H
#define ELECTRONICRESOURCE_H

#include "Resource.h"

class ElectronicResource : public Resource {
private:
    string isbn;
    string fileFormat;
    double fileSizeMB;
    string url;

public:
    ElectronicResource();
    ElectronicResource(int id, const string& isbn, const string& title,
                       const string& author, const string& publisher,
                       const string& fileFormat, double fileSizeMB,
                       const string& url, int totalCopies);
    ~ElectronicResource();

    string getIsbn() const;
    string getFileFormat() const;
    double getFileSizeMB() const;
    string getUrl() const;

    void setIsbn(const string& isbn);
    void setFileFormat(const string& fileFormat);
    void setFileSizeMB(double fileSizeMB);
    void setUrl(const string& url);

    string getType() const override;
    string getInfo() const override;
    void display() const override;
    void displayBrief() const override;
    string serialize() const override;

    static bool isValidIsbn(const string& isbn);
};

#endif
