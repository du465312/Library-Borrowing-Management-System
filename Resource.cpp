#include "Resource.h"

Resource::Resource()
    : id(0), title(""), author(""), publisher(""),
      totalCopies(0), availableCopies(0) {
}

Resource::Resource(int id, const string& title, const string& author,
                   const string& publisher, int totalCopies)
    : id(id), title(title), author(author), publisher(publisher) {
    if (totalCopies > 0) {
        this->totalCopies = totalCopies;
        this->availableCopies = totalCopies;
    } else {
        this->totalCopies = 1;
        this->availableCopies = 1;
    }
}

Resource::~Resource() {}

int Resource::getId() const { return id; }
string Resource::getTitle() const { return title; }
string Resource::getAuthor() const { return author; }
string Resource::getPublisher() const { return publisher; }
int Resource::getTotalCopies() const { return totalCopies; }
int Resource::getAvailableCopies() const { return availableCopies; }

void Resource::setTitle(const string& title) { this->title = title; }
void Resource::setAuthor(const string& author) { this->author = author; }
void Resource::setPublisher(const string& publisher) { this->publisher = publisher; }
void Resource::setTotalCopies(int totalCopies) {
    if (totalCopies > 0) {
        int diff = totalCopies - this->totalCopies;
        this->totalCopies = totalCopies;
        this->availableCopies += diff;
        if (this->availableCopies < 0) this->availableCopies = 0;
    }
}

bool Resource::isAvailable() const { return availableCopies > 0; }

bool Resource::borrow() {
    if (availableCopies > 0) {
        availableCopies--;
        return true;
    }
    return false;
}

bool Resource::returnBook() {
    if (availableCopies < totalCopies) {
        availableCopies++;
        return true;
    }
    return false;
}
