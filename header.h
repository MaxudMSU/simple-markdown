#ifndef HEADER_H
#define HEADER_H

#include "abstract_text.h"
#include "containers.h"

class Header : public Abstract_text{
 public:
  explicit Header(const wchar_t *str, unsigned long level);
  ~Header(){
    delete[] str_;
  };
  virtual unsigned long count_symbols() const override{
    return length_;
  }
  unsigned long get_level() const{
    return level_;
  }
  virtual unsigned long count_words() const override{
    return words_; 
  }
  virtual int print([[maybe_unused]] const DisplayParameters& display) const override;

 private:
  wchar_t *str_;
  unsigned long level_;
  unsigned long length_;
  unsigned long words_;
};

#endif