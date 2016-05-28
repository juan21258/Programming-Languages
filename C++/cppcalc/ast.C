#include "ast.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "calculator.h"

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}


BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

string AddNode::ewe(){
  string left = getLeftSubTree()->ewe();
  string right = getRightSubTree()->ewe();
  stringstream ss;
  ss << left << endl;
  ss << right << endl;
  ss << "#Add" << endl;
  ss << "operator2 := M[sp+0]" << endl;
  ss << "operator1 := M[sp+1]" << endl;
  ss << "operator1 := operator1 + operator2" << endl;
  ss << "sp := sp + one" << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}
string SubNode::ewe(){
  string left = getLeftSubTree()->ewe();
  string right = getRightSubTree()->ewe();
  stringstream ss;
  ss << left << endl;
  ss << right << endl;
  ss << "#Sub" << endl;
  ss << "operator2 := M[sp+0]" << endl;
  ss << "operator1 := M[sp+1]" << endl;
  ss << "operator1 := operator1 - operator2" << endl;
  ss << "sp := sp + one" << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

string TimesNode::ewe(){
  string left = getLeftSubTree()->ewe();
  string right = getRightSubTree()->ewe();
  stringstream ss;
  ss << left << endl;
  ss << right << endl;
  ss << "#Times" << endl;
  ss << "operator2 := M[sp+0]" << endl;
  ss << "operator1 := M[sp+1]" << endl;
  ss << "operator1 := operator1 * operator2" << endl;
  ss << "sp := sp + one" << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

DivNode::DivNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivNode::evaluate() {
  return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

string DivNode::ewe(){  
  string left = getLeftSubTree()->ewe();
  string right = getRightSubTree()->ewe();
  stringstream ss;
  ss << left << endl;
  ss << right << endl;
  ss << "#Divide" << endl;
  ss << "operator2 := M[sp+0]" << endl;
  ss << "operator1 := M[sp+1]" << endl;
  ss << "operator1 := operator1 / operator2" << endl;
  ss << "sp := sp + one" << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModNode::evaluate() {
   return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

string ModNode::ewe(){
  string left = getLeftSubTree()->ewe();
  string right = getRightSubTree()->ewe();
  stringstream ss;
  ss << left << endl;
  ss << right << endl;
  ss << "#Module" << endl;
  ss << "operator2 := M[sp+0]" << endl;
  ss << "operator1 := M[sp+1]" << endl;
  ss << "operator1 := operator1 % operator2" << endl;
  ss << "sp := sp + one" << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}

string NumNode::ewe(){
  stringstream ss;
  ss << "\n #push("<<val<<")\n";
  ss << "sp := sp - one " << endl;
  ss << "operator1 := " << val << endl;
  ss << "M[sp+0] := operator1" << endl;
  return ss.str();
}

IdNode::IdNode(char c):AST(),var(c){}

int IdNode::evaluate(){
  return calc->varid(var);
}

string IdNode::ewe(){
  stringstream ss;
  
  return ss.str();
}

RecallNode::RecallNode() :
 AST() {}

RecallNode::~RecallNode(){}

int RecallNode::evaluate() {
  return calc->recall();
}

string RecallNode::ewe(){
  stringstream ss;
  ss << "\n #Recall" << endl;
  ss << "sp := sp - one" << endl;
  ss << "M[sp+0] := memory" << endl;
  return ss.str();
}  
StoreNode::StoreNode(AST* sub) : UnaryNode(sub) { }

StoreNode::~StoreNode() {}

int StoreNode::evaluate() {
  int mem;
  mem = getSubTree()->evaluate();
  calc->store(mem);
  return mem;
};

string StoreNode::ewe(){
  stringstream ss;
  ss << "\n #Store" << endl;
  ss << " memory := M[sp+0]" << endl;
  return getSubTree()->ewe() + ss.str();
}

MemOpNode::MemOpNode(AST* sub,int opk) : UnaryNode(sub) { 
  this->opk = opk;
}

int MemOpNode::evaluate() {
  int mem;
  mem = getSubTree()->evaluate();
  int rt = calc->recall();
  //calc->store(rm-mem);
  if(opk==0){
    calc->store(rt-mem);
    return rt-mem;
  }
  if(opk==1){
    //mem = getSubTree()->evaluate();
    calc->store(rt+mem);
    return rt+mem;
  }

};

string MemOpNode::ewe(){

  stringstream ss;
  string left = getSubTree()->ewe();
  if(opk==0){
    
    ss << left << endl;
    ss << "\n #Memory Minus" << endl;
    ss << "\n operator2 := M[sp+0]" << endl;
    ss << "memory := memory - operator2" << endl;
    return ss.str();
  }
  else if(opk==1){
    
    ss << left << endl;
    ss << "\n #Memory Plus" << endl;
    ss << "\n operator2 := M[sp+0]" << endl;
    ss << "memory := memory + operator2" << endl;
    return ss.str();
  }
}

ClearNode::ClearNode() : AST() {}

int ClearNode::evaluate() {
  calc->store(0);
  return calc->recall();
};

string ClearNode::ewe(){
  stringstream ss;
  ss << "\n #Clear" << endl;
  ss << "memory := zero" << endl;
  ss << "sp := sp - one" << endl;
  ss << "M[sp+0] := memory" << endl;
  return ss.str();
}

