#include "header.h"

#include <string.h>
#include <iostream>

Header::Header(const wchar_t *str, unsigned long level){
  level_ = level;
  // очистка от повторяющихся пробелов
  bool first_space = false;
  int count = 0, space_count = 0;
  auto str_len = wcslen(str);
  wchar_t* new_str = new wchar_t[str_len];
  for (unsigned long i = 0; i < str_len && str[i] != L'\n'; i++){
    if (str[i] == L' ' && first_space){
      first_space = false;
      new_str[count] = str[i];
      space_count++;
      count++;
    }
    else if (str[i] == L' '){
      continue;
    }
    else {
      first_space = true;
      new_str[count] = str[i];
      count++;
    }
  }
  
  length_ = count;
  words_ = space_count;
  str_ = new wchar_t[length_];
  for (unsigned long i=0; i<length_; i++){
    str_[i] = new_str[i];
  }
  delete[] new_str;
}


int Header::print([[maybe_unused]] const DisplayParameters& display) const{
  int min_space = length_ + 2*level_;
  int left_otstup = (display.screen_width - min_space)/2;
  int right_otstup = display.screen_width - min_space - left_otstup;
  if (min_space > display.screen_width){
    fprintf(stderr, "\033[91mОшибка: слишком маленькая ширина экрана для отображения заголовка.\n\033[0m");
    return -1;
  }
  else{
    for (int i=0; i<display.screen_width; i++){
      std::wcout << L"#";
    }
    std::wcout << L"\n";
    for (unsigned long i=0; i<level_; i++){
      std::wcout << L"#";
    }
    for (int i=0; i<left_otstup; i++){
      std::wcout << L" ";
    }
    for (unsigned long i=0; i<length_; i++){
      if (display.in_file) 
        std::wcout << str_[i];
      else 
        wprintf(L"\033[33m%lc\033[0m", str_[i]);
    }
    for (int i=0; i<right_otstup; i++){
      std::wcout << L" ";
    }
    for (unsigned long i=0; i<level_; i++){
      std::wcout << L"#";
    }
    std::wcout << "\n";
    for (int i=0; i<display.screen_width; i++){
      std::wcout << L"#";
    }
    std::wcout << L"\n";
    return 1;
  }
}