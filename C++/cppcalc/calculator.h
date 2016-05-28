#ifndef calculator_h
#define calculator_h

#include <string>
#include <map> 
using namespace std;


class Calculator {
 public:
   Calculator();
   //int evalf(string in[],bool enter);
   int eval(string exr, bool enter);
   void store(int val);
   int recall();
   int varid(char c);
   string ewe(string expr, bool enter);

 private:
   int memory;
};

extern Calculator* calc;
extern map<char,int>vi;

#endif

