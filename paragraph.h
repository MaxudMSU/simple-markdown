#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "abstract_text.h"
#include "containers.h"

class Paragraph : public Abstract_text{
 public:
  Paragraph(const NewString& str, bool is_start);
  ~Paragraph(){
    delete[] str_;
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
  int length_;
  bool is_start_;
  int words_;
};

#endif