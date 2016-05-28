#ifndef scanner_h
#define scanner_h

#include <iostream>
#include "token.h"

class Scanner {
public:
  Scanner(istream* in, bool enter);
  ~Scanner();

  Token* getToken();
  void putBackToken();
 
private:
  Scanner();

  istream* inStream;
  int lineCount;
  int colCount;

  bool needToken;
  Token* lastToken;
};

#endif
  
  

