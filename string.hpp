#pragma once

#include <stdlib.h>

#include <iostream>
#include <vector>

class String {
 private:
  ////////Parameters////////
  size_t size_;
  size_t capacity_;
  char* chars_;

 public:
  ////////Constructors/////////

  String();

  String(size_t size, char character);
  String(const char* chars);

  String(const String& str);

  /////////Destructor//////////

  ~String();

  ////////Operators////////////

  String& operator=(const String& str);

  String& operator=(const char& str);

  String& operator=(const char* str);

  char& operator[](size_t index);

  char operator[](size_t index) const;

  friend bool operator==(const String& str0, const String& str);

  // friend bool operator==(const String & str0, const char* c);

  friend bool operator!=(const String& str0, const String& str);

  // friend bool operator!=(const String & str0, const char* c);

  friend bool operator<=(const String& str0, const String& str);

  // friend bool operator<=(const String & str0, const char* c);

  friend bool operator>=(const String& str0, const String& str);

  // friend bool operator>=(const String & str0, const char* c);

  friend bool operator>(const String& str0, const String& str);

  // friend bool operator>(const String & str0, const char* c);

  friend bool operator<(const String& str0, const String& str);

  // friend bool operator<(const String str0, const char* c);

  friend String operator+(const String& str0, const String& str);

  String& operator+=(const String& str);

  friend std::istream& operator>>(std::istream& is, String& str);

  friend std::ostream& operator<<(std::ostream& os, String str);

  String operator*(size_t n) const;

  String& operator*=(size_t n);

  ///////////Methods///////////

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& Front();

  char& Back();

  char Front() const;

  char Back() const;

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  const char* Data() const;

  char* Data();

  std::vector<String> Split(const String& delim = " ");

  String Join(const std::vector<String>& strings) const;
};
