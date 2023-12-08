#include "code_block.h"

#include <iostream>

CodeBlock::CodeBlock(wchar_t* str){
  bool first_space = false;
  int space_count = 0;
  int count = 0;
  for (int i = 0; str[i] != L'\n'; i++) {
    if (str[i] == L' ' && first_space) {
      first_space = false;
      space_count++;
      count++;
    } else if (str[i] == L' ') {
      count++;
    } else {
      first_space = true;
      count++;
    }
  }
  length_ = count;
  words_ = space_count;
  str_ = new wchar_t[length_];
  for (int i=0; i<length_; i++)
    *(str_ + i) = str[i];
}

int CodeBlock::print([[maybe_unused]] const DisplayParameters& display) const{
  std::wcout << L"@   ";
  int out_len = length_ > (display.screen_width - 4) ? (display.screen_width - 4) : length_;
  for (int i = 0; i < out_len; i++) {
    if (display.in_file) {
      std::wcout << str_[i];
    } else {
      wprintf(L"\033[92m%lc\033[0m", str_[i]);
    }
  }
  std::wcout << L"\n";
  return 0;
}