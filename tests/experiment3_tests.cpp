#include "Library.h"
#include <climits>
#include <cstdlib>
#include <sstream>
#include <type_traits>

void check(bool condition) {
    if (!condition) { std::cerr << "Check failed" << std::endl; std::exit(1); }
}

int main() {
    static_assert(std::is_base_of<Resource, Book>::value, "Book inherits Resource");
    static_assert(std::is_base_of<Resource, Magazine>::value, "Magazine inherits Resource");
    static_assert(std::is_base_of<Resource, ElectronicResource>::value, "ElectronicResource inherits Resource");

    Book book(1, "9787111421905", "Book", "Author", "Publisher", 2);
    Magazine magazine(2, "Magazine", "0254-4164", "2026-10", "Publisher", 1);
    ElectronicResource electronic(3, "Tutorial", "https://example.com", "PDF", 1);
    check(book.getId() == 1 && book.getTotalCopies() == 2);
    check(magazine.getIssue() == "2026-10" && electronic.getFormat() == "PDF");
    Resource& base = book;
    check(base.borrow() && book.getAvailableCopies() == 1);
    check(!base.setTotalCopies(0));
    check(base.returnBook() && !base.returnBook());
    check(base.setTotalCopies(0) && !base.borrow());

    Library lib;
    lib.addUser("s001", "Student", 1);
    lib.addBook("9787111421905", "Book", "Author", "Publisher", 2);
    lib.addMagazine("Magazine", "0254-4164", "2026-10", "Publisher", 1);
    lib.addElectronicResource("Tutorial", "https://example.com", "PDF", 1);
    lib.addMagazine("Bad", "", "", "", 0);
    check(lib.getResourceCount() == 3);
    for (int id = 1; id <= 3; ++id) {
        check(lib.borrowResource(1, id));
        check(!lib.borrowResource(1, id == 1 ? 2 : 1));
        check(!lib.removeResource(id));
        check(!lib.changeResourceCopies(id, -lib.findResource(id)->getTotalCopies()));
        check(lib.returnBook(id));
        check(!lib.returnBook(id));
    }
    check(!lib.borrowResource(999, 1) && !lib.borrowResource(1, 999));
    check(!lib.returnBook(999) && !lib.removeResource(999));
    check(lib.changeResourceCopies(1, 3));
    check(lib.findResource(1)->getTotalCopies() == 5);
    check(!lib.changeResourceCopies(1, INT_MAX));
    check(lib.changeResourceCopies(1, -5));
    check(!lib.borrowResource(1, 1));
    check(lib.changeResourceCopies(1, 1));
    check(lib.borrowBook(*lib.findUser(1), *lib.findBook(1)));
    check(lib.returnBook(4));

    std::ostringstream output;
    std::streambuf* previous = std::cout.rdbuf(output.rdbuf());
    check(lib.displayResource(1));
    check(lib.displayResource(2));
    check(lib.displayResource(3));
    std::cout.rdbuf(previous);
    check(output.str().find("ISBN") != std::string::npos);
    check(output.str().find("ISSN") != std::string::npos);
    check(output.str().find("PDF") != std::string::npos);

    for (int id = 1; id <= 3; ++id) check(lib.removeResource(id));
    check(lib.getResourceCount() == 0 && lib.getRecordCount() == 4);
    lib.addBook("9787111421905", "New", "Author", "Publisher", 1);
    check(lib.findResource(4) != nullptr && lib.findResource(1) == nullptr);
    std::cout << "All experiment 3 checks passed." << std::endl;
}
