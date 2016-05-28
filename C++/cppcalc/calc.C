#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
#include "parser.h"
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Calculator* calc;

map<char, int>vi;
int main(int argc, char* argv[]) {
  int auxarg=argc;
  char m;
  string arg;
  //string aux = argv[1];
  string finf;
  string codigoewe;
  ofstream archivo("a.ewe");
  string as;
  string line;
   if(argc == 1){
     while(!cin.eof()){
       cout << "> ";
       try{
	 getline(cin, line);
	 calc = new Calculator();
	 int result = calc->eval(line, true);
	 cout << "= " << result << endl;
	 delete calc;
       }
       catch(Exception ex){
	 cout << "* parser error" << endl;
	 delete calc;
       }
     }
   }else if(argc == 2){
     string aux = argv[1];
     
     if(aux.compare("-c")==0){
       while(!cin.eof()){
	 //cout << ">";
	 //try{
	 cout << ">";
	 //getline(cin, line);
	 //calc = new Calculator();
	 try{
	   getline(cin, line);
	   calc = new Calculator();
	   string res = calc->ewe(line,false);
	   string ini = "\n#Expresion:" + line + "\n";
	   ini = ini + "\n# Instrucciones antes del recorrido del arbol abstracto sintactico";
	   ini = ini + "\n sp := 1000\n one := 1\n zero := 0\n memory := zero";
	   string fin = "\n #  Write result";
	   fin = fin + "\n operator1 := M[sp+0]";
	   fin = fin + "\n sp := sp - one";
	   fin = fin + "\n writeInt(operator1)";
	   //string codigoewe = ini + res + fin; 
	   //delete calc;
	   //}catch(Exception ex){}
	   codigoewe += ini + res + fin;
	   delete calc;
	 }catch(Exception ex){}
       }
       //ofstream archivo("a.ewe");
       finf = finf + "\n end: halt"; 
       finf = finf + "\n equ memory    M[0]";
       finf = finf + "\n equ one       M[1]";
       finf = finf + "\n equ zero      M[2]";
       finf = finf + "\n equ operator1 M[3]";
       finf = finf + "\n equ operator2 M[4]";
       finf = finf + "\n equ sp        M[5]";
       finf = finf + "\n equ stack     M[6]\n";
       codigoewe += finf;
       archivo << codigoewe;
       archivo.close();
     }else if(argc == 3){
       //for(int i=1;i<argc;i++){
       ifstream in(argv[2]);
       while(!in.eof()){
	 try{
	   getline(in, line);
	   in >> as;
	   calc = new Calculator();
	   string res = calc->ewe(as,false);
	   string ini = "\n#Expresion:" + line + "\n";
	   ini = ini + "\n# Instrucciones antes del recorrido del arbol abstracto sintactico";
	   ini = ini + "\n sp := 1000\n one := 1\n zero := 0\n memory := zero";
	   string fin = "\n #  Write result";
	   fin = fin + "\n operator1 := M[sp+0]";
	   fin = fin + "\n sp := sp - one";
	   fin = fin + "\n writeInt(operator1)";
	   //string codigoewe = ini + res + fin; 
	   //delete calc;
	   //}catch(Exception ex){}
	   codigoewe += ini + res + fin;
	   delete calc;
	 }catch(Exception ex){}
       }
       finf = finf + "\n end: halt"; 
       finf = finf + "\n equ memory    M[0]";
       finf = finf + "\n equ one       M[1]";
       finf = finf + "\n equ zero      M[2]";
       finf = finf + "\n equ operator1 M[3]";
       finf = finf + "\n equ operator2 M[4]";
       finf = finf + "\n equ sp        M[5]";
       finf = finf + "\n equ stack     M[6]\n";
       codigoewe += finf;
       archivo << codigoewe;
       archivo.close();
       
       //cout << "se hizo" << endl;
     }else if(argc >=1){
       try{
	 for(int i=1;i<argc;i++){
	   ifstream in(argv[i]);
	   while(!in.eof()){
	     in >> line;
	     //convert file to a string
	     calc = new Calculator();
	     int result = calc->eval(line,false);
	     cout << "=" << result << endl;
	     //cout.flush();
	     delete calc;
	   }
	 }
     }
       catch(Exception ex) {}
       
   }
     else if(auxarg > 1){
       if(aux.compare("-v")==0){
	 // while(!cin.eof()){
	  cout << "> ";
	  for(int i =1;i < auxarg; i++){
	    string strvi=argv[i];
	    if((strvi.compare("-v")==0)){
	      //vi.insert(pair<char,int>(a,b));
	      //cin >>vi;
	      //vi >> line;
	      if(i+1<auxarg){
		string indicar = argv[i+1];
		char varin;
		int valor = 0;
		string valor2;
		varin = indicar[0];
		for(int i = 2; i<indicar.length();i++){
		  valor2 += indicar[i];
		}
		valor=atoi(valor2.c_str());
		vi[varin]=valor;
	      }
	      else {
		throw ParseError;
	      }
	      
	      //analize the variables
	    } 
	  }
	  while(!cin.eof()){
	    try{
	      getline(cin, line);
	      //cin >> m;
	      calc = new Calculator();
	      int result = calc->eval(line,false);
	      cout << "= " << result << endl;
	      delete calc;
	    }catch(Exception ex) {
	      cout << "* parser error" << endl;
	    }
	  }
       }
     }
   }
}

