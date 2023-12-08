#ifndef NUM_LIST_H
#define NUM_LIST_H

#include <iostream>

#include "abstract_text.h"

class NumList : public Abstract_text{
 public:
  NumList(const NewString& str, wchar_t* marker, int nesting);
  ~NumList(){
    delete[] str_;
    delete[] marker_;
  }
  virtual unsigned long count_symbols() const override{
    return length_ - 1;
  }
  virtual unsigned long count_words() const override{
    return words_; 
  }
  virtual int print([[maybe_unused]] const DisplayParameters& display) const;

 private:
  wchar_t* str_;
  wchar_t* marker_;
  int length_;
  int nesting_;
  int words_;
};

#endif