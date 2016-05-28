#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

bool auxenter;
Parser::Parser(istream* in,bool enter) {
   scan = new Scanner(in,enter);
   auxenter = enter;
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return Prog();
}

AST* Parser::Prog() {
   AST* result = Expr();
   Token* t = scan->getToken();

   if (t->getType() != eof) {
     if (auxenter) cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl; 
     throw ParseError;
   }

   return result;
}

AST* Parser::Expr() { 
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
   Token* t = scan->getToken();
   if (t->getType() == add) {
      return RestExpr(new AddNode(e,Term()));
   }
   if (t->getType() == sub)
      return RestExpr(new SubNode(e,Term()));
   scan->putBackToken();
   return e;
}

AST* Parser::Term() { 
  return RestTerm(Storable()); 
}

AST* Parser::RestTerm(AST* e) {

  Token* t = scan->getToken();

  if (t->getType() == times) {
    return RestTerm(new TimesNode(e,Term()));
  }
  if (t->getType() == divide){
      return RestTerm(new DivNode(e,Term()));
  }
  if (t->getType() == mod){
      return RestTerm(new ModNode(e,Term()));
  }
  scan->putBackToken();

  return e;
 
}

AST* Parser::Storable() {
  AST* result = Factor();
  result = MemOperation(result);
  return result;
}

AST* Parser::MemOperation(AST* f){
  Token* t = scan->getToken();
  if(t->getType()==keyword){
    if(t->getLex().compare("S")==0)return new StoreNode(f);
    else if(t->getLex().compare("M")==0)return new MemOpNode(f,0);
    else if(t->getLex().compare("P")==0)return new MemOpNode(f,1);
    
    // throw ParseError;
  }
  scan->putBackToken();
  return f;
}

AST* Parser::Factor() {
   AST *ret;
   Token* t = scan->getToken();
   
   if(t->getType() == identifier){
     istringstream in(t->getLex());
     char var;
     in >> var;
     return new IdNode(var);
   }
   
   else if (t->getType() == number) {
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
   }
   else if (t->getType() == keyword) {
     if(t->getLex() == "R"){
       return new RecallNode();
     }
     else if(t->getLex() == "C"){
       return new ClearNode();
     }
     else {
       if (!auxenter)cout << "Syntax Error: Expected R, found token at column " << t->getCol() << endl;
       throw ParseError;
     }
   }
   else if (t->getType() == lparen) {
     ret = Expr();
     t = scan->getToken();
     if (t->getType() != rparen) {
       if (!auxenter) cout << "Syntax Error: Expected ), found token at column " << t->getCol() << endl;
       throw ParseError;
     }
     return ret;
   }
   if(!auxenter)cout << "Expected number,identifier, R or (" << endl;
   throw ParseError;
}

  
