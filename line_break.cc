#include "line_break.h"

#include <iostream>

int LineBreak::print([[maybe_unused]] const DisplayParameters& display) const{
  std::wcout << L"\n";
  return 0;
}