#include "ElectronicResource.h"
#include <iostream>

ElectronicResource::ElectronicResource() : Resource() {}
ElectronicResource::ElectronicResource(int id, const string& title, const string& url,
                                       const string& format, int licenses)
    : Resource(id, title, licenses), url(url), format(format) {}
string ElectronicResource::getUrl() const { return url; }
string ElectronicResource::getFormat() const { return format; }
void ElectronicResource::setUrl(const string& url) { this->url = url; }
void ElectronicResource::display() const {
    cout << "[电子资源] ";
    Resource::display();
    cout << " | 格式: " << format << " | 地址: " << url
         << " | 数量表示可同时借阅的授权数" << endl;
}
