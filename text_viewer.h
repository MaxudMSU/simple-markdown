#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#include <wchar.h>
#include <vector>

#include "containers.h"
#include "paragraph.h"
#include "header.h"
#include "marked_list.h"
#include "num_list.h"
#include "code_block.h"
#include "line_break.h"

class TextViewer {
 public:
  TextViewer(FILE* stream);
  void print(const DisplayParameters& display);
  void print_stats();

 private:
  std::vector<Abstract_text*> text_;
};



#endif