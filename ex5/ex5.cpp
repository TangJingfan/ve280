#include "ex5.h"
#include <iostream>

// default constructor
bookInventory::bookInventory()
    : books(new Book[MAX_BOOKS]), numBooks(0), empty(true), size(MAX_BOOKS) {}

// constructor with parameter
bookInventory::bookInventory(int maxBooks)
    : numBooks(0), empty(true), size(maxBooks) {
  if (maxBooks < 1 || maxBooks > MAX_BOOKS) {
    throw Exception("Invalid size.");
  }
  books = new Book[maxBooks];
}

// deconstructor
bookInventory::~bookInventory() { delete[] books; }

// check invariants
bool bookInventory::repOK() {
  // check inventory size
  if (numBooks > size) {
    return false;
  }
  // check empty
  if ((numBooks == 0) != empty) {
    return false;
  }
  // check null pointer
  if (books == nullptr) {
    return false;
  }
  // check whether numBooks is valid
  for (unsigned int i = 0; i < size; i++) {
    if (i < numBooks) {
      // first numBooks of books should be valid
      if (books[i].author.empty() || books[i].title.empty()) {
        return false;
      }
    } else {
      // last few should be empty
      if (!books[i].author.empty() || !books[i].title.empty()) {
        return false;
      }
    }
  }
  return true;
}

void bookInventory::addBook(const Book &book) {
  if (numBooks >= size) {
    throw Exception("Inventory is full.");
  }
  books[numBooks++] = book;
  empty = false;
}

// Remove a book
void bookInventory::removeBook(int ID) {
  if (ID < 1 || ID > static_cast<int>(numBooks)) {
    throw Exception("Invalid book ID.");
  }
  for (unsigned int i = ID - 1; i < numBooks - 1; i++) {
    books[i] = books[i + 1];
  }
  books[numBooks - 1] = Book();
  numBooks--;
  if (numBooks == 0) {
    empty = true;
  }
}

// Print the inventory
void bookInventory::printInventory() const {
  if (empty) {
    throw Exception("Inventory is empty.");
  }
  for (unsigned int i = 0; i < numBooks; i++) {
    std::cout << "Book ID: " << i + 1 << std::endl;
    std::cout << "Title: " << books[i].title << std::endl;
    std::cout << "Author: " << books[i].author << std::endl;
  }
}