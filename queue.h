#pragma once
//190110
/*
#include <iostream>
#include "queue.h"

int main() {
  queue<int> a, b, c;    //如何在声明时初始化
  for (int i = 0; i < 10010; i++) a.push(i);
  for (int i = 0; i < 10; i++) b.push(i);
  for (int i = 0; i < 10050; i++) c.push(i);
  std::cout << a.front() << "  " << a.back() << "  " << a.empty() << std::endl;
  a.pop(); b = a; c = a;
  std::cout << a.front() << "  " << a.back() << "  " << a.size() << std::endl;
  std::cout << b.front() << "  " << b.back() << "  " << b.size() << std::endl;
  std::cout << c.front() << "  " << c.back() << "  " << c.size() << std::endl;
  return 0;
}
*/

template <typename T> struct node {
  T data;
  node<T> *prev, *next;
  node() : prev(nullptr), next(nullptr) {}
  node(T e, node<T> *p = nullptr, node<T> *s = nullptr) : data(e), prev(p), next(s) {}
};

template <typename T> class queue {
protected:
  node<T> *head_, *tail_;
  int size_;
public:
  queue();
  ~queue();
  void operator= (const queue<T> &V);
  bool empty() { return size_ == 0; }
  int size() { return size_; }
  void push(T e);
  void pop();  //非空
  T front() { return (head_->next)->data; }  //非空
  T back() { return (tail_->prev)->data; }   //非空
};

template <typename T>
queue<T>::queue() {
  head_ = new node<T>; tail_ = new node<T>;
  head_->prev = nullptr; head_->next = tail_;
  tail_->next = nullptr; tail_->prev = head_;
  size_ = 0;
  return;
}

template <typename T>
queue<T>::~queue() {
  node<T> *p = head_->next, *del = nullptr;
  while (p != tail_) {
    del = p; p = p->next; delete del;
  }
  delete head_; head_ = nullptr;
  delete tail_; tail_ = nullptr;
  size_ = 0;
  return;
}

template <typename T>
void queue<T>::operator= (const queue<T> &V) {
  node<T> *p1, *p2, *low, *del;
  bool flag = true;
  for (p1 = head_->next, p2 = V.head_->next; p2 != V.tail_; p1 = p1->next, p2 = p2->next) {
    if (p1 != tail_) p1->data = p2->data;
    else {
      while (p2 != V.tail_) {
        low = tail_->prev, p1 = new node<T>(p2->data, low, tail_);
        low->next = p1; tail_->prev = p1; p2 = p2->next;
      }
      flag = false;
      break;
    }
  }
  if (flag && p1 != tail_) {
    low = p1->prev;
    while (p1 != tail_) {
      del = p1; p1 = p1->next; delete del;
    }
    low->next = tail_;
    tail_->prev = low;
  }
  size_ = V.size_;
  return;
}

template <typename T>
void queue<T>::push(T e) {
  node<T> *low = tail_->prev, *add = new node<T>(e, low, tail_);
  low->next = add; tail_->prev = add; size_++;
  return;
}

template <typename T>
void queue<T>::pop() {
  node<T> *del = head_->next;
  if (del == tail_) return;
  node<T> *high = del->next;
  high->prev = head_; head_->next = high;
  delete del; size_--;
  return;
}
