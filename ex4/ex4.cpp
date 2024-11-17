#include "ex4.h"

#include <iostream>
#include <string>

bookInventory::bookInventory() : numBooks(0) {
  for (int i = 0; i < MAX_BOOKS; i++) {
    books[i] = Book();
  }
};

void bookInventory::addBook(const Book &book) {
  if (numBooks == MAX_BOOKS) {
    throw Exception("The inventory is full.");
  }
  books[numBooks] = book;
  numBooks++;
}

int bookInventory::searchBook(const std::string &title) const {
  for (int i = 0; i < numBooks; i++) {
    if (books[i].title == title) {
      return i + 1;
    }
  }
  throw Exception("Book " + title + " not found.");
}

void bookInventory::setBook(const Book &book, int ID) {
  if (!(1 <= ID && ID <= MAX_BOOKS)) {
    throw Exception("Invalid book ID.");
  }
  if (ID > numBooks) {
    books[numBooks] = book;
    numBooks++;
  } else {
    books[ID - 1] = book;
  }
}

Book bookInventory::viewBook(int ID) const {
  if (!(1 <= ID && ID <= numBooks)) {
    throw Exception("Invalid book ID.");
  }
  return books[ID - 1];
}

void bookInventory::removeBook(int ID) {
  if (!(1 <= ID && ID <= numBooks)) {
    throw Exception("Invalid book ID.");
  }
  for (int i = ID; i < numBooks; i++) {
    books[i - 1] = books[i];
  }
  books[numBooks - 1] = Book();
  numBooks--;
}

void bookInventory::printInventory() const {
  if (numBooks == 0) {
    throw Exception("The inventory is empty.");
  }
  for (int i = 0; i < numBooks; i++) {
    std::cout << "Book ID: " << i + 1 << std::endl;
    std::cout << "Title: " << books[i].title << std::endl;
    std::cout << "Author: " << books[i].author << std::endl;
    std::cout << "Status: ";
    if (books[i].isAvailable) {
      std::cout << "available" << std::endl;
    } else {
      std::cout << "not available" << std::endl;
    }
  }
}