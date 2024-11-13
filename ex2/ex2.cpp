#include "ex2.h"
#include <iostream>

Library initLibrary() {
  Library lib;
  lib.numBooks = 0;
  return lib;
}

void addBook(Library &lib, std::string title, std::string author) {
  if (lib.numBooks < MAX_BOOKS) {
    Book newBook;
    newBook.ID = lib.numBooks + 1;
    newBook.title = title;
    newBook.author = author;
    newBook.isAvailable = true;
    lib.books[lib.numBooks] = newBook;
    lib.numBooks++;
  } else {
    std::cout << "The library is full." << std::endl;
  }
}

void borrowBook(Library &lib, int ID) {
  if (ID >= 1 && ID <= lib.numBooks) {
    if (lib.books[ID - 1].isAvailable) {
      lib.books[ID - 1].isAvailable = false;
      std::cout << "Book " << lib.books[ID - 1].title << " is borrowed."
                << std::endl;
    } else {
      std::cout << "Book " << lib.books[ID - 1].title << " is not available."
                << std::endl;
    }
  } else {
    std::cout << "Invalid book ID." << std::endl;
  }
}

void returnBook(Library &lib, int ID) {
  if (ID >= 1 && ID <= lib.numBooks) {
    if (!lib.books[ID - 1].isAvailable) {
      lib.books[ID - 1].isAvailable = true;
      std::cout << "Book " << lib.books[ID - 1].title << " is returned."
                << std::endl;
    } else {
      std::cout << "Book " << lib.books[ID - 1].title
                << " is already available." << std::endl;
    }
  } else {
    std::cout << "Invalid book ID." << std::endl;
  }
}

void printLibrary(const Library &lib) {
  if (lib.numBooks == 0) {
    std::cout << "The library is empty." << std::endl;
  } else {
    for (int i = 0; i < lib.numBooks; i++) {
      std::cout << "Book ID: " << lib.books[i].ID << std::endl;
      std::cout << "Title: " << lib.books[i].title << std::endl;
      std::cout << "Author: " << lib.books[i].author << std::endl;
      if (lib.books[i].isAvailable) {
        std::cout << "Status: available" << std::endl;
      } else {
        std::cout << "Status: not available" << std::endl;
      }
    }
  }
}