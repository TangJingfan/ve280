#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include "dlist.h"

template <class T> Dlist<T>::Dlist() : first(nullptr), last(nullptr) {}

template <class T>
Dlist<T>::Dlist(const Dlist &l) : first(nullptr), last(nullptr) {
  copyAll(l);
}

template <class T> Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
  if (this != &l) {
    removeAll();
    copyAll(l);
  }
  return *this;
}

template <class T> Dlist<T>::~Dlist() { removeAll(); }

template <class T> bool Dlist<T>::isEmpty() const { return first == nullptr; }

template <class T> void Dlist<T>::insertFront(T *op) {
  node *newNode = new node{nullptr, nullptr, op};
  if (isEmpty()) {
    first = last = newNode;
  } else {
    newNode->next = first;
    first->prev = newNode;
    first = newNode;
  }
}

template <class T> void Dlist<T>::insertBack(T *op) {
  node *newNode = new node{nullptr, nullptr, op};
  if (isEmpty()) {
    first = last = newNode;
  } else {
    newNode->prev = last;
    last->next = newNode;
    last = newNode;
  }
}

template <class T> T *Dlist<T>::removeFront() {
  if (isEmpty())
    throw emptyList();
  node *oldNode = first;
  T *data = oldNode->op;
  first = first->next;
  if (first) {
    first->prev = nullptr;
  } else {
    last = nullptr;
  }
  delete oldNode;
  return data;
}

template <class T> T *Dlist<T>::removeBack() {
  if (isEmpty())
    throw emptyList();
  node *oldNode = last;
  T *data = oldNode->op;
  last = last->prev;
  if (last) {
    last->next = nullptr;
  } else {
    first = nullptr;
  }
  delete oldNode;
  return data;
}

template <class T> void Dlist<T>::removeAll() {
  while (!isEmpty()) {
    delete removeFront();
  }
}

template <class T> void Dlist<T>::copyAll(const Dlist &l) {
  for (node *curr = l.first; curr != nullptr; curr = curr->next) {
    insertBack(new T(*curr->op));
  }
}

#endif