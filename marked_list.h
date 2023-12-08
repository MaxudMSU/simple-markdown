#ifndef MARKED_LIST_H
#define MARKED_LIST_H

#include <wchar.h>
#include <iostream>

#include "abstract_text.h"

class MarkedList : public Abstract_text{
 public:
  MarkedList(const NewString& str, int nesting);
  ~MarkedList(){
    delete[] str_;
  }
  virtual unsigned long count_symbols() const override{
      return length_;
  }
  virtual unsigned long count_words() const override{
    return words_; 
  }
  virtual int print([[maybe_unused]] const DisplayParameters& display) const;

 private:
  wchar_t* str_;
  int length_;
  int nesting_;
  char marker_;
  int indent_;
  int words_;
};

#endif