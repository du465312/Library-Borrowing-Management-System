#ifndef ELECTRONICRESOURCE_H
#define ELECTRONICRESOURCE_H

#include "Resource.h"

class ElectronicResource : public Resource {
private:
    string url;
    string format;
public:
    ElectronicResource();
    ElectronicResource(int id, const string& title, const string& url,
                       const string& format, int licenses);
    string getUrl() const;
    string getFormat() const;
    void setUrl(const string& url);
    void display() const;
};

#endif
