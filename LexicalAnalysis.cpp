// LexicalAnalysis.cpp: implementation of the LexicalAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "LexicalAnalysis.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


LexicalAnalysis::LexicalAnalysis(ifstream *in) : fp(in)
{}

LexicalAnalysis::~LexicalAnalysis()
{

}



void LexicalAnalysis::addChar()
{
	lexeme+=nextChar;
}

int LexicalAnalysis::lex()
{

  
  return -1;
}
