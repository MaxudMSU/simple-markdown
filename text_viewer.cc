// TODO: убрать повторяющиеся фрагменты кода при обработке списков разного уровня вложенности.

#include "text_viewer.h"

bool is_digit(wchar_t c){
  return (c >= L'0' && c <= L'9');
}

TextViewer::TextViewer(FILE* stream){
  wchar_t* line = new wchar_t[1000];
  NewString* prev_line;
  wchar_t* marker;
  int check = 0, check_line_break = 0, check_paragraph_start = 1;
  unsigned long nesting = 0;
  while (fgetws(line, 1000, stream) != NULL) {
    switch (check){
    case 0: //если начало абзаца (либо после переноса строки, либо в начале текста)
      if (line[0] == L'\n'){
        if (check_line_break){
          check_line_break = 0;
          check_paragraph_start = 1;
          text_.push_back(new LineBreak());
        }
        break;
      }
      else if (line[0] == L'#'){
        unsigned long i = 1;
        while (line[i] == L'#'){
          i++;
        }
        if (line[i] == L' '){
          text_.push_back(new Header(line+i+1, i));
          text_.push_back(new LineBreak());
          check_line_break = 1;
          break;
        }
        else
          break;
      }
      else if (line[0] == L'*' && line[1] == L' '){
        prev_line = new NewString();
        nesting = 0;
        int i = 2;
        while (line[i++] != L'\n');
        line[i-1] = L'\0';
        prev_line->append(line+2, i-3);
        check = 1;
        break;
      }

      else if (is_digit(line[0])){
        int i = 1;
        while (is_digit(line[i])){
          i++;
        }
        if (line[i] == L'.' && line[i+1] == L' '){
          int ni = i+2;
          marker = new wchar_t[100];
          for (int k = 0; k<=i+1; k++){
            marker[k] = line[k];
          }
          marker[i+2] = L'\0';
          
          prev_line = new NewString();
          nesting = 0;
          i += 2;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line+ni, i-1-ni);
          check = 3;
          break;
        }
        else{
          prev_line = new NewString();
          int i = 0;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);

          check = 3;
          check_line_break = 1;
          break;
        }
      }
      else if (line[0] == L' '){
        int i = 1;
        while (line[i] == L' ' && i != 3){
          i++;
        }
        text_.push_back(new CodeBlock(line+i));
        check_line_break = 1;
        break;
      }
      else {
        prev_line = new NewString();
        int i = 0;
        while (line[i++] != L'\n');
        line[i-1] = L' ';
        line[i] = L'\0';
        prev_line->append(line, i);

        check = 2;
        check_line_break = 1;
        // check_paragraph_start = 0;
        break;
      }
    case 1: // если предыдущий абзац был маркированным списком
      if (line[0] == L'\n'){
        text_.push_back(new MarkedList(*prev_line, nesting));
        delete prev_line;
        if (check_line_break){
          check_line_break = 0;
          check_paragraph_start = 1;
          text_.push_back(new LineBreak());
        }
        check = 0;
        break;
      }
      else if (line[0] == L'*' && line[1] == L' '){
        text_.push_back(new MarkedList(*prev_line, nesting));
        delete prev_line;
        prev_line = new NewString();
        nesting = 0;
        int i = 2;
        while (line[i++] != L'\n');
        line[i-1] = L'\0';
        prev_line->append(line+2, i-3);
        check_line_break = 1;
        break;
      }
      else if (is_digit(line[0])){
        int i = 1;
        while (is_digit(line[i])){
          i++;
        }
        if (line[i] == L'.' && line[i+1] == L' '){
          text_.push_back(new MarkedList(*prev_line, nesting));
          delete prev_line;
          int ni = i+2;
          marker = new wchar_t[100];
          for (int k = 0; k<=i+1; k++){
            marker[k] = line[k];
          }
          marker[i+2] = L'\0';
          
          prev_line = new NewString();
          nesting = 0;
          i += 2;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line+ni, i-1-ni);
          check = 3;
          break;
        }
        else{
          int i = 0;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);

          check = 3;
          check_line_break = 1;
          break;
        }
      }
      else if (line[0] == L' '){
        int counter = 1;
        while (line[counter] == L' '){
            counter++;
        }
        if (line[counter] == L'*' && line[counter+1] == L' '){
          text_.push_back(new MarkedList(*prev_line, nesting));
          delete prev_line;
          prev_line = new NewString();
          int max_nest = nesting + 1;
          int half_count = counter/2;
          nesting = half_count > max_nest ? max_nest : half_count;
          int i = counter;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line+counter+2, i-3-counter);
          break;
        }
        else if(is_digit(line[counter])){
          int i = counter + 1;
          while (is_digit(line[i])){
            i++;
          }
          if (line[i] == L'.' && line[i+1] == L' '){
            text_.push_back(new MarkedList(*prev_line, nesting));
            delete prev_line;
            int max_nest = nesting + 1;
            int half_count = counter/2;
            nesting = half_count > max_nest ? max_nest : half_count;
            int ni = i+2;
            marker = new wchar_t[100];
            for (int k = counter; k < ni; k++){
              marker[k-counter] = line[k];
            }
            marker[i+2-counter] = L'\0';
            
            prev_line = new NewString();
            i += 2;
            while (line[i++] != L'\n');
            line[i-1] = L'\0';
            prev_line->append(line+ni, i-1-ni);
            check = 3;
            break;
          }
          else{
            int i = 0;
            while (line[i++] != L'\n');
            line[i-1] = L'\0';
            prev_line->append(line, i-1);

            check = 3;
            check_line_break = 1;
            break;
          }
        }
        else{
          int i = 0;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);
          break;
        }
      }
      else{
        int i = 0;
        while (line[i++] != L'\n');
        line[i-1] = L'\0';
        prev_line->append(line, i-1);
        break;
      }

    case 3:
      if (line[0] == L'\n'){
        text_.push_back(new NumList(*prev_line, marker, nesting));
        delete prev_line;
        delete[] marker;
        if (check_line_break){
          check_line_break = 0;
          check_paragraph_start = 1;
          text_.push_back(new LineBreak());
        }
        check = 0;
        break;
      }
      else if (line[0] == L'*' && line[1] == L' '){
        text_.push_back(new NumList(*prev_line, marker, nesting));
        delete prev_line;
        delete[] marker;
        prev_line = new NewString();
        nesting = 0;
        int i = 2;
        while (line[i++] != L'\n');
        line[i-1] = L'\0';
        prev_line->append(line+2, i-3);
        check = 1;
        check_line_break = 1;
        break;
      }
      else if (is_digit(line[0])){
        int i = 1;
        while (is_digit(line[i])){
          i++;
        }
        if (line[i] == L'.' && line[i+1] == L' '){
          text_.push_back(new NumList(*prev_line, marker, nesting));
          delete prev_line;
          delete[] marker;
          int ni = i+2;
          marker = new wchar_t[100];
          for (int k = 0; k<=i+1; k++){
            marker[k] = line[k];
          }
          marker[i+2] = L'\0';
          
          prev_line = new NewString();
          nesting = 0;
          i += 2;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line+ni, i-1-ni);
          check = 3;
          break;
        }
        else{
          int i = 0;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);

          check = 3;
          check_line_break = 1;
          break;
        }
      }
      else if (line[0] == L' '){
        int counter = 1;
        while (line[counter] == L' '){
            counter++;
        }
        if (line[counter] == L'*' && line[counter+1] == L' '){
          text_.push_back(new NumList(*prev_line, marker, nesting));
          delete prev_line;
          delete[] marker;
          prev_line = new NewString();
          int max_nest = nesting + 1;
          int half_count = counter/2;
          nesting = half_count > max_nest ? max_nest : half_count;
          int i = counter;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line+counter+2, i-3-counter);
          check = 1;
          break;
        }
        else if(is_digit(line[counter])){
          int i = counter + 1;
          while (is_digit(line[i])){
            i++;
          }
          if (line[i] == L'.' && line[i+1] == L' '){
            text_.push_back(new NumList(*prev_line, marker, nesting));
            delete prev_line;
            delete[] marker;
            int max_nest = nesting + 1;
            int half_count = counter/2;
            nesting = half_count > max_nest ? max_nest : half_count;
            int ni = i+2;
            marker = new wchar_t[100];
            for (int k = counter; k < ni; k++){
              marker[k-counter] = line[k];
            }
            marker[i+2-counter] = L'\0';
            
            prev_line = new NewString();
            i += 2;
            while (line[i++] != L'\n');
            line[i-1] = L'\0';
            prev_line->append(line+ni, i-1-ni);
            check = 3;
            break;
          }
          else{
            int i = 0;
            while (line[i++] != L'\n');
            line[i-1] = L'\0';
            prev_line->append(line, i-1);

            check = 3;
            check_line_break = 1;
            break;
          }
        }
        else{
          int i = 0;
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);
          break;
        }
      }
      else{
        int i = 0;
        while (line[i++] != L'\n');
        line[i-1] = L'\0';
        prev_line->append(line, i-1);

        check = 3;
        check_line_break = 1;
        break;
      }
    
    case 2: // если предыдущий абзац был обычным
      if (line[0] == L'\n'){
        text_.push_back(new Paragraph(*prev_line, check_paragraph_start));
        delete prev_line;
        if (check_line_break){
          check_line_break = 0;
          check_paragraph_start = 1;
          text_.push_back(new LineBreak());
        }
        check = 0;
        break;
      }
      else if (line[0] == L'-'){
        int i = 1;
        while (line[i++] == L'-');
        if ((i >= 7) && (line[i-1] == L'\n')){
          check_line_break = 1;
          text_.push_back(new Header(prev_line->get_str(), 0));
          text_.push_back(new LineBreak());
          check = 0;
          delete prev_line;
          break;
        }
        else{
          while (line[i++] != L'\n');
          line[i-1] = L'\0';
          prev_line->append(line, i-1);
          check_line_break = 1;
          break;
        }
      }
      else{
        int i = 0;
        while (line[i++] != L'\n');
        line[i-1] = L' ';
        line[i] = L'\0';
        prev_line->append(line, i);
        check_line_break = 1;
        break;
      }

    default:
      break;
    }
  }
  switch (check){
  case 1:
    text_.push_back(new MarkedList(*prev_line, nesting));
    delete prev_line;
    break;
  case 3:
    text_.push_back(new NumList(*prev_line, marker, nesting));
    delete prev_line;
    delete[] marker;
    break;
  case 2:
    text_.push_back(new Paragraph(*prev_line, check_paragraph_start));
    delete prev_line;
    break;
  }
  delete[] line;
}

void TextViewer::print(const DisplayParameters& display){
  if (display.check() == -1)
    return;
  int print_code;
  for (const auto& elem : text_){
    print_code = elem->print(display);
    if (print_code == -1)
      break;
    delete elem;
  }
}

void TextViewer::print_stats(){
  int total_length = 0, total_words = 0;
  for (const auto& elem : text_){
    total_length += elem->count_symbols();
    total_words += elem->count_words();
  }
  std::cerr << "Количество символов в тексте: " << total_length << "\nКоличество слов в тексте: " << total_words << "\n";
}