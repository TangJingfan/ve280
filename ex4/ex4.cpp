#include "ex4.h"

#include <string>

bookInventory::bookInventory() : numBooks(0) {
  for (int i = 0; i < MAX_BOOKS; i++) {
    books[i] = Book();
  }
};

void bookInventory::addBook(const Book &book) {
  if (numBooks == MAX_BOOKS) {
    throw Exception("The inventory is full.");
  } else {
    books[numBooks] = book;
    numBooks++;
  }
}

int bookInventory::searchBook(const std::string &title) const {
  for (int i = 0; i < numBooks; i++) {
    if (books[i].title == title) {
      return i;
    }
  }
  throw Exception("Book " + title + " not found.");
}