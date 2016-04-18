// SyntaxAnalysis.cpp: implementation of the SyntaxAnalysis class.
//
//////////////////////////////////////////////////////////////////////
/*
#include "SyntaxAnalysis.h"
#include <iostream>
#include <string>


SyntaxAnalysis::SyntaxAnalysis(string in)
{
	LA.setNewInput(in);
	cout<<"input:"<<in<<endl;
	nextToken = LA.lex();
}

SyntaxAnalysis::~SyntaxAnalysis()
{
}

void SyntaxAnalysis::setNewInput(string in)
{
	LA.setNewInput(in);
	cout<<"input:"<<in<<endl;
	nextToken = LA.lex();
}

void SyntaxAnalysis::syntax()
{
	
	expr();
	if (nextToken==STOP) cout<<"Syntax is correct\n";
	else { cout<<"Error\n"; exit(1); }

}

void SyntaxAnalysis::expr()
{
	term();
	while (nextToken == PLUS_CODE){
		nextToken = LA.lex();
		term();
	}

}

void SyntaxAnalysis::term()
{

	if (nextToken==IDENT || nextToken==INT_LIT) {
		nextToken = LA.lex();
	}
	else { cout<<"Error\n"; exit(1); }
}
*/
