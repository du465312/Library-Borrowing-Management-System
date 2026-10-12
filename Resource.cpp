#include "Resource.h"
#include <iostream>

Resource::Resource() : id(0), totalCopies(0), availableCopies(0) {}

Resource::Resource(int id, const string& title, int totalCopies)
    : id(id), title(title), totalCopies(totalCopies > 0 ? totalCopies : 1),
      availableCopies(this->totalCopies) {}

int Resource::getId() const { return id; }
string Resource::getTitle() const { return title; }
int Resource::getTotalCopies() const { return totalCopies; }
int Resource::getAvailableCopies() const { return availableCopies; }
void Resource::setTitle(const string& title) { this->title = title; }

bool Resource::setTotalCopies(int totalCopies) {
    const int borrowed = this->totalCopies - availableCopies;
    if (totalCopies < 0 || totalCopies < borrowed) return false;
    this->totalCopies = totalCopies;
    availableCopies = totalCopies - borrowed;
    return true;
}

bool Resource::isAvailable() const { return availableCopies > 0; }
bool Resource::borrow() {
    if (!isAvailable()) return false;
    --availableCopies;
    return true;
}
bool Resource::returnBook() {
    if (availableCopies >= totalCopies) return false;
    ++availableCopies;
    return true;
}
void Resource::display() const {
    cout << "资源ID: " << id << " | 名称: " << title
         << " | 可借/总量: " << availableCopies << "/" << totalCopies;
}
