#pragma once
//190110
/*
#include <iostream>
#include "list.h"

int main() {
  list<int> a, b, c;    //如何在声明时初始化
  int arr1[10050], arr2[1050], arr3[1050];
  for (int i = 0; i < 10010; i++) a.push_back(i); a.push_front(233);
  std::cout << a.front() << "  " << a.back() << "  " << a.size() << std::endl;

  a.pop_back(); a.pop_front(); a.remove(11); a.unique();
  std::cout << a.front() << "  " << a.back() << "  " << a.size() << std::endl;

  a.clear();
  for (int i = 0; i < 10010; i++) a.push_back(i);
  for (int i = 0; i < 1010; i++)  b.push_back(i + 1111);
  for (int i = 0; i < 10050; i++) c.push_back(i + 2222);
  b = a; c = a;
  std::cout << a.echo(arr1, 10050) << std::endl;
  std::cout << b.echo(arr2, 1050) << std::endl;
  std::cout << c.echo(arr3, 1050) << std::endl;
  std::cout << arr1[0] << "  " << arr1[22] << "  " << arr1[55] << "  " << arr1[68] << std::endl;
  std::cout << arr2[0] << "  " << arr2[22] << "  " << arr2[55] << "  " << arr2[68] << std::endl;
  std::cout << arr3[0] << "  " << arr3[22] << "  " << arr3[55] << "  " << arr3[68] << std::endl;
  return 0;
}
*/

template <typename T> struct node {
  T data;
  node<T> *prev, *next;
  node() : prev(nullptr), next(nullptr) {}
  node(T e, node<T> *p = nullptr, node<T> *s = nullptr) : data(e), prev(p), next(s) {}
};

template <typename T> class list {
protected:
  node<T> *head_, *tail_;
  int size_;
public:
  list();
  ~list() { clear(); delete head_; head_ = nullptr; delete tail_; tail_ = nullptr; }
  void operator= (const list<T> &V);

  int size() { return size_; }
  bool resize(int len, T e);
  bool empty() { return size_ == 0; }
  void sort();
  void reverse();

  void push_back(T e);
  void push_front(T e);
  bool insert(int posi, T e) { return insert(posi, 1, e); }
  bool insert(int posi, int num, T e);

  bool pop_back();
  bool pop_front();
  bool erase(int a, int b);  //删除区间 [a, b)
  int remove(T e);
  int unique();
  void clear();

  int echo(T a[], int sum);  //将list中的数据依次赋值到数组
  T front() { return (head_->next)->data; }
  T back() { return (tail_->prev)->data; }
};

template <typename T>
list<T>::list() {
  head_ = new node<T>; tail_ = new node<T>;
  head_->next = tail_; head_->prev = nullptr;
  tail_->prev = head_; tail_->next = nullptr;
  size_ = 0;
  return;
}

template <typename T>
void list<T>::operator= (const list<T> &V) {
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
bool list<T>::resize(int len, T e) {
  if (len >= size_) return insert(size_, len - size_, e);
  else return erase(len + 1, size_);
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;
  for (node<T> *lo = head_->next; lo != tail_->prev; lo = lo->next) {
    for (node<T> *hi = lo->next; hi != tail_; hi = hi->next) {
      if (lo->data > hi->data) { T temp = lo->data; lo->data = hi->data; hi->data = temp; }
    }
  }
  return;
}

template <typename T>
void list<T>::reverse() {
  if (size_ < 2) return;
  node<T> *lo = head_->next, *hi = tail_->prev;
  while (hi->next != lo && hi != lo) {
    T temp = lo->data; lo->data = hi->data; hi->data = temp;
    lo = lo->next; hi = hi->prev;
  }
  return;
}

//添加

template <typename T>
void list<T>::push_back(T e) {
  node<T> *lo = tail_->prev, *add = new node<T>(e, lo, tail_); size_++;
  lo->next = add; tail_->prev = add;
  return;
}

template <typename T>
void list<T>::push_front(T e) {
  node<T> *hi = head_->next, *add = new node<T>(e, head_, hi); size_++;
  hi->prev = add; head_->next = add;
  return;
}

template <typename T>
bool list<T>::insert(int posi, int num, T e) {
  if (posi < 0 || posi > size_) return false;
  node<T> *lo = head_, *hi, *add;
  for (int i = 0; i < posi; i++) lo = lo->next;
  hi = lo->next; size_ += num;
  while (num--) {
    add = new node<T>(e);
    lo->next = add; add->prev = lo; lo = add;
  }
  lo->next = hi; hi->prev = lo;
  return true;
}

//删除

template <typename T>
bool list<T>::pop_back() {
  if (size_ < 1) return false;
  node<T> *del = tail_->prev;
  tail_->prev = del->prev;
  (del->prev)->next = tail_;
  delete del;
  return true;
}

template <typename T>
bool list<T>::pop_front() {
  if (size_ < 1) return false;
  node<T> *del = head_->next;
  head_->next = del->next;
  (del->next)->prev = head_;
  delete del;
  return true;
}

template <typename T>
bool list<T>::erase(int a, int b) {  //删除区间 [a, b)
  if (a >= b || a < 1 || b > size_) return false;
  node<T> *hi = head_, *lo, *del = nullptr;
  for (int i = 0; i < a; i++) hi = hi->next;
  lo = hi->prev;
  for (int i = a; i < b; i++) {
    del = hi; hi = hi->next; delete del;
  }
  lo->next = hi; hi->prev = lo; size_ -= (b - a);
  return true;
}

template <typename T>
int list<T>::remove(T e) {
  int oldSize = size_;
  node<T> *check = head_->next, *del = nullptr;
  while (check != tail_) {
    if (check->data == e) {
      (check->prev)->next = check->next;
      (check->next)->prev = check->prev;
      size_--; del = check; check = check->next; delete del;
    }
    else check = check->next;
  }
  return oldSize - size_;
}

template <typename T>
int list<T>::unique() {
  if (size_ < 2) return 0;
  int oldSize = size_;
  node<T> *lo = head_->next, *hi = (head_->next)->next, *del = nullptr;
  while (hi != tail_) {
    if (lo->data == hi->data) {
      del = hi; hi = hi->next;
      lo->next = hi; hi->prev = lo;
      delete del; size_--;
    }
    else { lo = hi; hi = hi->next; }
  }
  return oldSize - size_;
}

template <typename T>
void list<T>::clear() {
  node<T> *p = head_->next, *del = nullptr;
  while (p != tail_) {
    del = p; p = p->next; delete del;
  }
  head_->next = tail_; tail_->prev = head_; size_ = 0;
  return;
}

//访问

template <typename T>
int list<T>::echo(T a[], int sum) {
  int i = 0;
  for (node<T> *p = head_->next; p != tail_; p = p->next) {
    a[i] = p->data; i++;
    if (i == sum) return i;
  }
  return i;
}
