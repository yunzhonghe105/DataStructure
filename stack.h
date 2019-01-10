#pragma once
//190109
/*
#include <iostream>
#include "stack.h"

int main() {
  stack<int> a, b;  //如何在声明时初始化？
  for (int i = 0; i < 100; i++) a.push(i);
  for (int i = 0; i < 11; i++) b.push(i);
  std::cout << a.top() << "  " << a.size() << "  " << a.empty() << std::endl;
  a.pop(); b = a;
  std::cout << a.top() << "  " << a.size() << "  " << a.empty() << std::endl;
  b.pop();
  std::cout << b.top() << "  " << b.size() << "  " << b.empty() << std::endl;
  return 0;
}
*/

template <typename T> class stack {
protected:
  T *elem_;
  int size_, capacity_;
  void expand();
  void shrink();
public:
  stack() { elem_ = new T[10010]; size_ = 0; capacity_ = 10010; }
  ~stack() { delete[] elem_; elem_ = nullptr; }
  void operator=(const stack<T> &V);
  void push(T e) { *(elem_ + size_) = e; size_++; expand(); return; }
  void pop() { size_--; shrink(); return; }  // size_ > 0
  T top() { return *(elem_ + size_ - 1); }   // size_ > 0
  bool empty() { return size_ == 0; }
  int size() { return size_; }
};

template <typename T>
void stack<T>::expand() {
  if (size_ < capacity_ - 100) return;
  T *temp = elem_;
  elem_ = new T[capacity_ *= 2];
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(temp + i);
  delete[] temp;
  return;
}

template <typename T>
void stack<T>::shrink() {
  if (size_ > capacity_ / 4 || capacity_ <= 10010) return;
  T *temp = elem_;
  elem_ = new T[capacity_ /= 2];
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(temp + i);
  delete[] temp;
  return;
}

template <typename T>
void stack<T>::operator=(const stack<T> &V) {
  T *del = elem_;
  capacity_ = V.capacity_;
  size_ = V.size_;
  elem_ = new T[capacity_];
  if (del != nullptr) delete[] del;
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(V.elem_ + i);
  return;
}
