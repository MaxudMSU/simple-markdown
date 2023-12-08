#include "marked_list.h"

#include <string.h>
#include <iostream>

MarkedList::MarkedList(const NewString& str, int nesting){
  nesting_ = nesting;
  
  bool first_space = false;
  int count = 0, space_count = 0;
  auto str_len =str.length();
  wchar_t* new_str = new wchar_t[str_len];
  for (unsigned long i = 0; i < str_len; i++){
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
  for (int i=0; i<length_; i++){
    *(str_ + i) = new_str[i];
  }
  delete[] new_str;
}

int MarkedList::print([[maybe_unused]] const DisplayParameters& display) const{
  for (int i=0; i<nesting_*2; i++){
    std::wcout << L' ';
  }
  
  if (display.in_file)
    std::wcout << display.mark_symb << L" ";
  else
    wprintf(L"\033[96m%lc \033[0m ", display.mark_symb);

  int shift = 2 + nesting_*2;
  int str_shift = display.list_indent + nesting_*2;
  int i = 0;
  int str_num = 0;
  int true_screen_width;
  int word_counter = 0, word_start = 0;
  while (str_[i] != L'\0') {
    if (!str_num)
      true_screen_width = display.screen_width - shift;
    else {
      true_screen_width = display.screen_width - str_shift;
    }
    for (int j = 0; j < true_screen_width && str_[i] != L'\0'; ++j) {
      if (j == true_screen_width - 1){ // смотрим на последний влезающий символ
        if (word_counter == 0) // если это первая буква
          continue;
        if (word_counter == 1){ // если предыдущая была первой
          if (str_[i] == L' ') {// если это пробел -> печатаем слово на строке
            std::wcout << str_[i-1]; // печатаем букву
            std::wcout << str_[i++]; // печатаем пробел
            word_counter = 0;
            word_start = i;
          }
          else if (str_[i+1] == L' ' || str_[i+1] == L'\0'){ // если это последняя буква в слове -> печатаем слово на строке
            std::wcout << str_[i-1]; // печатаем предыдущую букву
            std::wcout << str_[i]; // печатаем текущую букву
            word_counter = 0;
            i += 2; // пропускаем пробел
            word_start = i;
          }
          else { // если слово продолжается, то перенести нельзя
            continue;
          }
        }
        if (word_counter > 1) { // если до этого было больше двух букв
          if (str_[i] == L' '){ // если это пробел -> печатаем слово на строке
            for (int k = word_start; k < word_start + word_counter; k++)
              std::wcout << str_[k]; // печатаем слово
            std::wcout << str_[i++]; // печатаем сам пробел
            word_counter = 0;
            word_start = i;
          }
          else if (str_[i+1] == L' ' || str_[i+1] == L'\0'){ // если это последняя буква в слове -> печатаем слово на строке
            for (int k = word_start; k < word_start + word_counter; k++)
              std::wcout << str_[k]; // печатаем слово (до текущей буквы)
            std::wcout << str_[i];
            word_counter = 0;
            i += 2; // пропускаем пробел (по идее на следующей строке он не нужен)
            word_start = i;
          }
          else if (str_[i+2] == L' '){ // если после этого одна буква, то перенести нельзя
            continue;
          }
          else{ // если всё хорошо и можно переносить
            for (int k = word_start; k < word_start + word_counter; k++)
              std::wcout << str_[k]; // печатаем слово (до текущей буквы)
            std::wcout << L'-';
            word_counter = 0;
            word_start = i;
          }
        }
      }
      else if (str_[i] == L' ' || str_[i+1] == L'\0'){
        for (int k = word_start; k < word_start + word_counter; k++)
          std::wcout << str_[k];
        std::wcout << str_[i++];
        word_counter = 0;
        word_start = i;
      }
      else{
        word_counter++;
        i++;
      }
    }
    if (str_[i] != L'\0') {
      std::wcout << L'\n';
      for (int k = 0; k < str_shift; k++){
        std::wcout << L' ';
      }
      i = word_start;
      word_counter = 0;
      str_num++;
    }
  }
  std::wcout << L"\n";
  return 0;
}