// LexicalAnalysis.h: interface for the LexicalAnalysis class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


using namespace std;

class LexicalAnalysis  
{

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	ifstream *fp;

public:
	int lex();
	LexicalAnalysis(ifstream *fp);
	virtual ~LexicalAnalysis();




private:
	void addChar();
	void getChar();
};


#endif