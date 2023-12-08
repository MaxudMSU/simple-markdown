#include "line_break.h"

#include <wchar.h>

#include <iostream>

#include "containers.h"

int LineBreak::print([[maybe_unused]] const DisplayParameters& display) const{
  std::wcout << L"\n";
  return 0;
}