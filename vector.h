#pragma once
//190109
/*
#include <iostream>
#include "vector.h"

int main() {
  vector<int> a, b;  //如何在声明时初始化？
  a.reserve(222);
  for (int i = 0; i < 100; i++) a.push_back(i);
  for (int i = 0; i < 10; i++) b.push_back(i);
  std::cout << a.size() << "  " << a.empty() << std::endl;
  a.pop_back(); a.erase(22, 23); a[24] = 220;
  std::cout << a.size() << std::endl; b = a;
  for (int i = 11; i < 26; i++) std::cout << a[i] << "  ";
  std::cout << std::endl;
  for (int i = 11; i < 26; i++) std::cout << b[i] << "  ";
  return 0;
}
*/

template <typename T> class vector {
protected:
  T *elem_;
  int size_, capacity_;
  void expand();
  void shrink();
public:
  vector() { elem_ = new T[capacity_ = 10010]; size_ = 0; }
  ~vector() { delete[] elem_; elem_ = nullptr; }
  int size() { return size_; }
  bool empty() { return size_ == 0; }
  void reserve(int n);
  void push_back(T e);
  void pop_back();
  void erase(int lo, int hi);  //删除区间 [lo, hi)
  T& operator[] (int n) { return *(elem_ + n); }  // 0 <= n < size_
  void operator= (const vector<T> &V);
};

template <typename T>
void vector<T>::expand() {
  if (size_ < capacity_ - 100) return;
  T *temp = elem_;
  elem_ = new T[capacity_ *= 2];
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(temp + i);
  delete[] temp;
  return;
}

template <typename T>
void vector<T>::shrink() {
  if (size_ > capacity_ / 4 || capacity_ <= 10010) return;
  T *temp = elem_;
  elem_ = new T[capacity_ /= 2];
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(temp + i);
  delete[] temp;
  return;
}

template <typename T>
void vector<T>::reserve(int n) {
  if (capacity_ < n || capacity_ > n * 2 || capacity_ > n + 10010) {
    T *temp = elem_;
    elem_ = new T[capacity_ = n + 100];
    if (size_ > n) size_ = n;
    for (int i = 0; i < size_; i++) *(elem_ + i) = *(temp + i);
    delete[] temp;
  }
  return;
}

template <typename T>
void vector<T>::push_back(T e) {
  *(elem_ + size_) = e; size_++;
  expand();
  return;
}

template <typename T>
void vector<T>::pop_back() {
  size_--; shrink();
  return;
}

template <typename T>
void vector<T>::erase(int lo, int hi) {  //删除区间 [lo, hi)
  if (lo == hi) return;
  for (; hi < size_; lo++, hi++) *(elem_ + lo) = *(elem_ + hi);
  size_ = lo;
  shrink();
  return;
}

template <typename T>
void vector<T>::operator= (const vector<T> &V) {
  T *del = elem_;
  size_ = V.size_;
  capacity_ = V.capacity_;
  elem_ = new T[capacity_];
  for (int i = 0; i < size_; i++) *(elem_ + i) = *(V.elem_ + i);
  if (del != nullptr) delete[] del;
  return;
}
