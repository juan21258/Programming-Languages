#ifndef ast_h
#define ast_h
#include <iostream>
using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual int evaluate() = 0;
   virtual string ewe()=0;
};

class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};

class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;

 private:
   AST* subTree;
};

class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);
   
   int evaluate();
   string ewe();
};

class TimesNode : public BinaryNode {
 public:
   TimesNode(AST* left, AST* right);
   
   int evaluate();
   string ewe();
};

class DivNode : public BinaryNode {
 public:
   DivNode(AST* left, AST* right);
   
   int evaluate();
   string ewe();
};

class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   int evaluate();
   string ewe();
};

class ModNode : public BinaryNode {
 public:
   ModNode(AST* left, AST* right);

   int evaluate();
   string ewe();
};

class IdNode : public AST {
 public:
  IdNode(char c);
  int evaluate();
  string ewe();
 private:
  int var;
  
};
class NumNode : public AST {
 public:
   NumNode(int n);

   int evaluate();
   string ewe();

 private:
   int val;
};

class RecallNode : public AST {
  public:
  RecallNode();
  ~RecallNode();
  int evaluate();
  string ewe();
};

class StoreNode : public UnaryNode {
  public:
  StoreNode(AST* sub);
  ~StoreNode();
  int evaluate();
  string ewe();
};

class MemOpNode : public UnaryNode {
  public:
  int opk;
  MemOpNode(AST* sub, int opk);
  int evaluate();
  string ewe();
};

class ClearNode : public AST {
  public:
  //int def;
  ClearNode();
  int evaluate();
  string ewe();
};



#endif

