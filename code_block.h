#ifndef CODE_BLOCK_H
#define CODE_BLOCK_H

#include "abstract_text.h"

class CodeBlock : public Abstract_text{
 public:
  CodeBlock(wchar_t* str);
  ~CodeBlock(){
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
  int words_;
};

#endif