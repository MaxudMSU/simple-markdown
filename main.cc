// TODO: Add full help file to print it via -h option.

#include <errno.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wchar.h>

#include <cstring>
#include <iostream>
#include <locale>

#include "containers.h"
#include "text_viewer.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL, "ru_RU.UTF-8");
  char opts[] = "f:t:m:r:hvi";
  int opt;
  static struct option long_opt[] = {
    {"file", 2, 0, 'f'},
    {"indent", 2, 0, 't'},
    {"marker", 2, 0, 'm'},
    {"redline", 2, 0, 'r'},
    {"help", 0, 0, 'h'},
    {"version", 0, 0, 'v'},
    {"in-file", 0, 0, 'i'},
    {0,0,0,0}
  };

  int optIdx;

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  auto screen_width = w.ws_col;

  DisplayParameters display(screen_width);

  char* filename;
  FILE* stream = stdin;

  while((opt = getopt_long(argc, argv, opts, long_opt, &optIdx)) != -1){
    switch (opt) {
      case 'f':
        filename = optarg;
        stream = fopen(filename, "r");
        if (stream == nullptr){
            std::cerr << "Can't open file '" << filename << "': " << strerror(errno);
            break;
        }
        break;
      case 't':
        if (optarg) display.list_indent = atoi(optarg);
        break;
      case 'm':
        if (optarg) display.mark_symb = optarg[0];
        break;
      case 'r':
        if (optarg) display.redline = atoi(optarg);
        break;
      case 'h':
        std::wcout << L"help is printed\n";
        break;
      case 'v':
        std::wcout << L"version 1.0\n";
        break;
      case 'i':
        display.in_file = true;
        display.screen_width = 100;
        break;
      case '?':
        std::wcout << L"undefined option -" << (wchar_t)optopt << L"\n";
        break;
    }
  }

  TextViewer text(stream);
  text.print_stats();
  text.print(display);
  fclose(stream);
  return 0;
}
