#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#include <vector>

#include "abstract_text.h"
#include "containers.h"


class TextViewer {
 public:
  TextViewer(FILE* stream);
  void print(const DisplayParameters& display);
  void print_stats();

 private:
  std::vector<Abstract_text*> text_;
};



#endif