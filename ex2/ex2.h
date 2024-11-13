#ifndef EX2_H
#define EX2_H
#include <string>
#define MAX_BOOKS 10

struct Book {
  int ID;
  std::string title;
  std::string author;
  bool isAvailable;
  // true when available; false when borrowed
};

struct Library {
  Book books[MAX_BOOKS];
  int numBooks;
};

Library initLibrary();
void addBook(Library &lib, std::string title, std::string author);
void borrowBook(Library &lib, int ID);
void returnBook(Library &lib, int ID);
void printLibrary(const Library &lib);
#endif
