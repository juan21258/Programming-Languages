#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
//#include "calc.C"

using namespace std;

extern map<char,int>vi;

Calculator::Calculator():
   memory(0)
{}

int Calculator::eval(string expr, bool enter) {

  Parser* parser = new Parser(new istringstream(expr),enter);
  
  AST* tree = parser->parse();
   
  int result = tree->evaluate();
  
  delete tree;
  
  delete parser;
  
  return result;
}

string Calculator::ewe(string expr, bool enter){
  
  Parser* parser = new Parser(new istringstream(expr), enter);
  
  AST* tree = parser->parse();
  
  string result = tree->ewe();
  
  delete tree;
  
  delete parser;
  
  return result;
}

int Calculator::varid(char c){
  /* //typedef pair<c,char>comp; */
  /* map<char,int>::iterator it; */
  /* //map<char,int>::iterator p = vi.find(c); */
  /* //for(map<char,int>::iterator it=vi.begin();it!=vi.end();it++){ */
  /* it = vi.find(c); */
  /* for(c='a';c<'z';c++){ */
  /*   if(vi.count(c)>0){ */
  /*     return calc->varid(c);       */
  /*   } */
  /*   else{ */
  /*     return calc->varid(c); */
  /*   } */
  /* } */
  /*   //return new IdNode(var); */
  /*   //} */
  return vi[c];
}


void Calculator::store(int val) {
  memory = val;
}

int Calculator::recall() {
  return memory;
}
