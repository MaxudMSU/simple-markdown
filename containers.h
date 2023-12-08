#ifndef DISPLAY_PARAMETERS_H
#define DISPLAY_PARAMETERS_H

#include <iostream>

struct DisplayParameters{
  int screen_width;
  int redline;
  int list_indent;
  wchar_t mark_symb;
  bool in_file;
  DisplayParameters(int sw) : screen_width(sw), redline(4), list_indent(2), mark_symb('*'), in_file(false) {}; 
  int check() const{
    if (redline >= screen_width){
      fprintf(stderr, "\033[91mОшибка: отступ красной строки (%d) больше ширины экрана (%d).\n\033[0m", redline, screen_width);
      return -1;
    }
    if (list_indent >= screen_width){
      fprintf(stderr, "\033[91mОшибка: отступ новой строки списка (%d) больше ширины экрана (%d).\n\033[0m", list_indent, screen_width);
      return -1;
    }
    return 0;
  }
};

class NewString{
 public:
  NewString();
	NewString(const NewString& copy);
	~NewString() { delete[] str_; };
	unsigned long length() const {
    return length_; 
  };
  const wchar_t* get_str() const {
    return str_; 
  };
	void append(const wchar_t *added, unsigned long _len);
	void append(const NewString& string) {
		this->append(string.str_, string.length() - 1);
	};
	wchar_t& operator[](unsigned long ind) const {
		if (ind < length_) {
			return str_[ind];
    } else {
      std::cerr << "index out of range\n"; // походу надо throw делать
      exit(0);
    }
	};
  
 private:
  wchar_t *str_;
	unsigned long length_;
};

// class TextContainer{
//  public:
//   TextContainer() : storage_(nullptr), size_(0), alloc_(0) {};
//   TextContainer(const TextContainer& copy);
//   ~TextContainer() {
//     delete storage_;
//   }
//   void push_back(Abstract_text* const &added);
//   Abstract_text*& operator[](int index) const;
//   unsigned long len(){
//     return size_;
//   }

//  private:
//   Abstract_text** storage_;
//   unsigned long size_, alloc_;
// };

#endif