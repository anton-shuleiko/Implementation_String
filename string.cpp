#include "string.hpp"

#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <limits>
#include <vector>

////////Constructors/////////

String::String() {
  this->size_ = 0;
  this->capacity_ = 0;
  this->chars_ = new char[1];
  this->chars_[0] = '\0';
}

String::String(size_t size, char character) {
  this->size_ = size;
  if (size == 0) {
    *this = String();
  }
  this->capacity_ = this->size_;
  this->chars_ = new char[this->capacity_ + 1];
  for (size_t i = 0; i < this->size_; i++) {
    this->chars_[i] = character;
  }
  this->chars_[size] = '\0';
}

String::String(const char* chars) {
  this->size_ = strlen(chars);
  if (this->size_ != 0) {
    this->capacity_ = 1;
    while (this->capacity_ <= this->size_) {
      this->capacity_ *= 2;
    }
  } else {
    this->capacity_ = 0;
  }
  this->chars_ = new char[this->capacity_ + 1];
  for (size_t i = 0; i < this->size_; i++) {
    this->chars_[i] = chars[i];
  }
  this->chars_[this->size_] = '\0';
}

String::String(const String& str) {
  this->capacity_ = str.capacity_;
  this->size_ = str.size_;
  this->chars_ = new char[this->capacity_ + 1];
  for (size_t i = 0; i <= this->size_; i++) {
    this->chars_[i] = str.chars_[i];
  }
}

/////////Destructor//////////

String::~String() { delete[] this->chars_; }

////////Operator////////////

String& String::operator=(const String& str) {
  if (*this != str) {
    delete[] this->chars_;
    this->capacity_ = str.capacity_;
    this->size_ = str.size_;
    this->chars_ = new char[this->capacity_ + 1];
    for (size_t i = 0; i < this->size_; i++) {
      this->chars_[i] = str.chars_[i];
    }
    this->chars_[this->size_] = '\0';
  }
  return *this;
}

String& String::operator=(const char* str) {
  String st(str);
  *this = st;
  return *this;
}

char& String::operator[](size_t index) { return this->chars_[index]; }

char String::operator[](size_t index) const { return this->chars_[index]; }

bool operator==(const String& str0, const String& str) {
  if (str0.size_ != str.size_) {
    return false;
  }
  for (size_t i = 0; i < str.size_; i++) {
    if (str0.chars_[i] != str.chars_[i]) {
      return false;
    }
  }
  return true;
}

/*bool operator==(const String str0, const char* c){
    const String str(c);
    return str0 == str;
}*/

bool operator!=(const String& str0, const String& str) {
  return !(str0 == str);
}

/*bool operator!=(const String & str0, const char* c){
    const String & str(c);
    return str0 != str;
}*/

bool operator<(const String& str0, const String& str) {
  size_t minim = std::min(str0.size_, str.size_);
  for (size_t i = 0; i <= minim; i++) {
    if (str0.chars_[i] < str.chars_[i]) {
      return true;
    }
  }
  return false;
}

/*bool operator<(const String & str0, const char* c){
    const String & str(c);
    return str0 < str;
}*/

bool operator>=(const String& str0, const String& str) { return !(str0 < str); }

/*bool operator>=(const String & str0, const char* c){
    const String & str(c);
    return str0 >= str;
}*/

bool operator>(const String& str0, const String& str) { return (str < str0); }

/*bool operator>(const String & str0, const char* c){
    const String & str(c);
    return str0 > str;
}*/

bool operator<=(const String& str0, const String& str) { return (str >= str0); }

/*bool operator<=(const String & str0, const char* c){
    const String str(c);
    return str0 <= str;
}*/

String operator+(const String& str0, const String& str) {
  String res;
  delete[] res.chars_;
  res.capacity_ = str0.capacity_ + str.capacity_;
  res.size_ = str0.size_ + str.size_;
  res.chars_ = new char[res.capacity_ + 1];
  for (size_t i = 0; i <= res.size_; i++) {
    if (i < str0.size_) {
      res.chars_[i] = str0.chars_[i];
    } else {
      res.chars_[i] = str.chars_[i - str0.size_];
    }
  }
  return res;
}

String& String::operator+=(const String& str) {
  char* res = new char[this->size_ + str.size_ + 1];
  memcpy(res, this->chars_, this->size_);
  memcpy(res + this->size_, str.chars_, str.size_);
  delete[] this->chars_;
  this->chars_ = res;
  this->size_ += str.size_;
  res[this->size_] = '\0';
  this->capacity_ = this->size_;
  return *this;
}

std::istream& operator>>(std::istream& is, String& str) {
  const size_t kMaxim = 250;
  char chars[kMaxim];
  is.getline(chars, sizeof(chars));
  str = String(chars);
  return is;
}

std::ostream& operator<<(std::ostream& os, String str) {
  for (size_t i = 0; i < str.size_; i++) {
    os << str.chars_[i];
  }
  return os;
}

String String::operator*(size_t n) const {
  String res;
  for (size_t i = 0; i < n; i++) {
    res += *this;
  }
  return res;
}

String& String::operator*=(size_t n) {
  String res;
  res.Reserve(this->size_ * n);
  for (size_t i = 0; i < n; i++) {
    res += *this;
  }
  *this = res;
  return *this;
}

///////////////////////////Methods//////////////////////////

void String::Clear() {
  this->size_ = 0;
  this->chars_[0] = '\0';
}

void String::PushBack(char character) {
  if (this->capacity_ == 0) {
    this->Reserve(1);
  }
  if (this->size_ == this->capacity_) {
    this->capacity_ *= 2;
    this->Reserve(this->capacity_);
  }
  this->chars_[this->size_] = character;
  this->size_++;
  this->chars_[this->size_] = '\0';
}

void String::PopBack() {
  if (this->size_ != 0) {
    this->size_--;
    this->chars_[this->size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  if (new_size > this->capacity_) {
    this->Reserve(new_size);
  }
  this->size_ = new_size;
  this->chars_[new_size] = '\0';
}

void String::Resize(size_t new_size, char character) {
  size_t sz = this->size_;
  this->Resize(new_size);
  for (size_t i = sz; i < new_size; i++) {
    this->chars_[i] = character;
  }
}

void String::Reserve(size_t new_cap) {
  if (new_cap > this->capacity_) {
    char* c = new char[new_cap + 1];
    for (size_t i = 0; i <= this->size_; i++) {
      c[i] = this->chars_[i];
    }
    delete[] this->chars_;
    this->chars_ = c;
  }
}

void String::ShrinkToFit() {
  if (this->size_ < this->capacity_) {
    char* c = new char[this->size_ + 1];
    for (size_t i = 0; i <= this->size_; i++) {
      c[i] = this->chars_[i];
    }
    delete[] this->chars_;
    this->chars_ = c;
    this->capacity_ = this->size_;
  }
}

void String::Swap(String& other) {
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->chars_, other.chars_);
}

char& String::Front() { return this->chars_[0]; }

char& String::Back() { return this->chars_[this->size_ - 1]; }

char String::Front() const { return this->chars_[0]; }

char String::Back() const { return this->chars_[this->size_ - 1]; }
bool String::Empty() const { return this->size_ == 0; }

size_t String::Size() const { return this->size_; }

size_t String::Capacity() const { return this->capacity_; }

const char* String::Data() const { return chars_; }

char* String::Data() { return chars_; }

std::vector<String> String::Split(const String& delim) {
  std::vector<String> res;
  size_t start = 0;
  size_t i = 0;
  char* substr = new char[delim.size_ + 1];
  for (; i < this->size_; i++) {
    if (this->size_ - i + 1 >= delim.size_) {
      memcpy(substr, this->chars_ + i, delim.size_);
    }
    substr[delim.size_] = '\0';
    if (String(substr) == delim) {
      char* smth = new char[i - start + 1];
      memcpy(smth, this->chars_ + start, i - start);
      smth[i - start] = '\0';
      res.push_back(String(smth));
      start = i + delim.size_;
      delete[] smth;
    }
  }
  char* smth = new char[i - start + 1];
  memcpy(smth, this->chars_ + start, i - start);
  smth[i - start] = '\0';
  res.push_back(String(smth));
  delete[] substr;
  delete[] smth;
  return res;
}

String String::Join(const std::vector<String>& strings) const {
  String res;
  for (size_t i = 0; i < strings.size(); i++) {
    res += strings[i];
    if (i != strings.size() - 1) {
      res += *this;
    }
  }
  return res;
}
