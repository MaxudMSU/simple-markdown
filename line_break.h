#ifndef LINE_BREAK_H
#define LINE_BREAK_H

#include <wchar.h>
#include "abstract_text.h"

class LineBreak : public Abstract_text{
 public:
  LineBreak() {};
  virtual unsigned long count_symbols() const override{
    return 0;
  }
  virtual unsigned long count_words() const override{
    return 0; 
  }
  virtual int print([[maybe_unused]] const DisplayParameters& display) const override;
};

#endif