#ifndef IO_H
#define IO_H

#include <cstdio>

class TokenizeReader {
public:
  TokenizeReader() = delete;
  TokenizeReader(FILE* file, int buffer_len);
  ~TokenizeReader();
  void Read(char* s, size_t& len, int max_len = std::numeric_limits<int>::max());
  bool HasNext();
  int NextInt();
private:
  bool EnsureRead();
  bool IsInValidCharacter(int c);

  FILE* file_;
  char* buffer_;
  int buffer_len_, pos_, read_n_;
  bool end_ = false;
};

TokenizeReader::TokenizeReader(FILE* file, int buffer_len)
  : file_(file), buffer_len_(buffer_len), pos_(0), read_n_(0) {
  buffer_ = new char[buffer_len_];
}

TokenizeReader::~TokenizeReader() {
  delete buffer_;
}

void TokenizeReader::Read(char *s, size_t &len, int max_len) {
  len = 0;
  while (EnsureRead() && IsInValidCharacter(buffer_[pos_])) pos_++;
  while (len < max_len && EnsureRead() && !IsInValidCharacter(buffer_[pos_])) {
    s[len++] = buffer_[pos_++];
  }
}

bool TokenizeReader::HasNext() {
  static size_t unused;
  Read(nullptr, unused, 0);
  return EnsureRead();
}

int TokenizeReader::NextInt() {
  static char buf[21];
  size_t len;
  int value;
  Read(buf, len, 20);
  if (len == 0) throw -1;
  buf[len] = 0;
  sscanf(buf, "%d", &value);
  return value;
}

bool TokenizeReader::EnsureRead() {
  if (pos_ < read_n_) {
    return true;
  } else if (end_) {
    return false;
  }
  read_n_ = ::fread(buffer_, 1 /* size */, buffer_len_, file_);
  pos_ = 0;
  end_ = read_n_ == 0;
  return !end_;
}

bool TokenizeReader::IsInValidCharacter(int c) {
  return c == ' ' || c == '\t' || c == '\n' || c == EOF;
}

#endif  // IO_H

