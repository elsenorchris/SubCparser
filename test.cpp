
#if !defined(_TEST_)
#define _TEST_


#include "LexicalAnalysis.h"

//tokens

#define T_program 302
#define T_var 303
#define T_const 304
#define T_type 305
#define T_function 306
#define T_return 307
#define T_begin 308
#define T_end 309
#define T_output 312
#define T_if 313
#define T_then 314
#define T_else 315
#define T_while 316
#define T_do 317
#define T_case 318
#define T_of 319
#define T_otherwise 321
#define T_repeat 322
#define T_for 323
#define T_until 324
#define T_loop 325
#define T_pool 326
#define T_exit 327
#define T_mod 334
#define T_and 335
#define T_or 336
#define T_not 337
#define T_read 338
#define T_succ 339
#define T_pred 340
#define T_chr 341
#define T_ord 342
#define T_eof 343
#define T_INTEGER 356
#define T_IDENTIFIER 357
#define T_comment 359
#define T_leq 360
#define T_geq 361
#define T_neq 362
#define T_swap 363
#define T_assignment 364
#define T_newLine 365
#define T_tab 366
#define T_UNKNOWN 0


using namespace std;

struct token_t {
	int type; // one of the token codes from above
	union {
		char stringValue[256]; // holds lexeme value if string/identifier
		int intValue; // holds lexeme value if integer
	} val; 
};

static unordered_map<string,double> reservedWords;

static void InitScanner(){
	reservedWords.insert({"program",302});
    reservedWords.insert({"var",303});
    reservedWords.insert({"const",304});
    reservedWords.insert({"type",305});
    reservedWords.insert({"function",306});
    reservedWords.insert({"return",307});
    reservedWords.insert({"begin",308});
    reservedWords.insert({"end",309});
    reservedWords.insert({"output",312});
    reservedWords.insert({"if",313});
    reservedWords.insert({"then",314});
    reservedWords.insert({"else",315});
    reservedWords.insert({"while",316});
    reservedWords.insert({"do",317});
    reservedWords.insert({"case",318});
    reservedWords.insert({"of",319});
    reservedWords.insert({"otherwise",321});
    reservedWords.insert({"repeat",322});
    reservedWords.insert({"for",323});
    reservedWords.insert({"until",324});
    reservedWords.insert({"loop",325});
    reservedWords.insert({"pool",326});
    reservedWords.insert({"exit",327});
    reservedWords.insert({"mod",334});
    reservedWords.insert({"and",335});
    reservedWords.insert({"or",336});
    reservedWords.insert({"not",337});
    reservedWords.insert({"read",338});
    reservedWords.insert({"succ",339});
    reservedWords.insert({"pred",340});
    reservedWords.insert({"chr",341});
    reservedWords.insert({"ord",342});
    reservedWords.insert({"eof",343});


}

static int ScanOneToken(ifstream *fp, struct token_t *token)
{
	int i;
	char ch, nextch;

	if (!(fp->get(ch))){
        return T_eof;
    }; // read next char from input stream

	while (ch==' ') // if necessary, keep reading til non-space char
		fp->get(ch); // (discard any white space)
    
    nextch=fp->peek();
    
	switch(ch) {

		case '{': { // comment
            token->val.stringValue[0] = ch;
			while(ch!='}') {
                for (i = 1; ch != '}'; i++) {
                    if(!(fp->get(ch))) {
                        return T_eof;
                    }
                    token->val.stringValue[i] = ch;
                }
            }
            return T_comment;
        }
            
        case '\n': { //new line
			token->type = T_newLine;
            return T_newLine;
        }
            
        case '<': {
            fp->get(ch);
            if (ch=='=') {
                token->type = T_leq; // ASCII value is used as token type
                return T_leq; // ASCII value used as token type
            } else {
                fp->unget();
                token->type = '<';
                return '<';
            }
        }
            
        case '>': {
            fp->get(ch);
            if (ch=='=') {
                token->type = T_geq; // ASCII value is used as token type
                return T_geq; // ASCII value used as token type
            } else {
                fp->unget();
                token->type = '>';
                return '>';
            }
        }
            
        case ':': {
            fp->get(ch);
            if (ch=='=') {
                if (ch==':') {
                    token->type = T_swap; 
                    return T_swap;
                } else {
                    token->type = T_assignment;
                    return T_assignment;
                }
                
            } else {
                fp->unget();
                token->type = ':';
                return ':';
            }
        }

		case ';': case ',': case '=': case '.': case '(': case ')': case '+': case '-': case '*': case '/': {
                token->type = ch; // ASCII value is used as token type
                return ch; // ASCII value used as token type
        }

		case 'A' ... 'Z': case 'a' ... 'z': case '_': {// ... and other upper letters
			token->val.stringValue[0] = ch;
            fp->get(ch);
			for (i = 1; isalnum(ch) || ch == '_'; i++) {
                token->val.stringValue[i] = ch;
                if (!fp->get(ch)) {
                    break;
                }
            }
			fp->unget();
			token->val.stringValue[i] = '\0'; // lookup reserved word
            
            unordered_map<string,double>::const_iterator got = reservedWords.find(token->val.stringValue);
            
            if ( got == reservedWords.end() )
                token->type = T_IDENTIFIER;
            else
                token->type = got->second;

			return token->type;
    }

		/*case 'a': case 'b': case 'c': // ... and other lower letters
			token->type = T_IDENTIFIER;
			token->val.stringValue[0] = ch;
			for (i = 1; islower(fp->get(ch)); i++) 
			token->val.stringValue[i] = ch; // gather lowercase
			ungetc(ch, fp);
			token->val.stringValue[i] = '\0';
			if (lookup_symtab(token->val.stringValue) == NULL)
			add_symtab(token->val.stringValue); // get symbol for ident
			return T_IDENTIFIER;*/

		case '0' ... '9': {
            
			token->type = T_INTEGER;
			token->val.intValue = ch - '0';
            fp->get(ch);
			while (isnumber(ch)) { // convert digit char to number
                token->val.intValue = token->val.intValue * 10 + ch - '0';
                fp->get(ch);
            }
			fp->unget();
			return T_INTEGER;
        }
            
        case '\t':{
            token->val.intValue = ch;
			token->type = T_tab;
            return T_tab;
        }

		case EOF:{
            return T_eof;
        }

		default: // anything else is not recognized
			token->val.intValue = ch;
			token->type = T_UNKNOWN;

			return T_UNKNOWN;
}
}


int main(int argc, char *argv[]) {
    cout<<"BEGIN"<<endl;
	struct token_t token;

	InitScanner();

	ifstream fin;
	fin.open("testing.txt");
    
    LexicalAnalysis LA(&fin);
	
	while (token!=STOP) {
		token = LA.lex();
		cout<<"lexeme: \""<<LA.lexeme<<"\"   token: "<<convertToken(token)<<endl;
	}
   

	int tokenType = ScanOneToken(&fin, &token);
	while (tokenType != T_end && tokenType != T_eof){
        
        if(tokenType==357 ) {
            cout<<tokenType <<" VALUE: "<< token.val.stringValue<< endl;
        } else if(tokenType==359) {
            cout<<tokenType <<" COMMENT: "<< token.val.stringValue<< endl;
        }
        else if (tokenType==356) {
            cout<<tokenType <<" INTEGER: "<< token.val.intValue<< endl;
        } else {
            cout<<tokenType <<endl;
        }
        
		tokenType = ScanOneToken(&fin, &token);
	}
    if (tokenType== T_end) {
        cout<<"Program is lexically correct!" <<endl;
    } else {
        cout<<"Program is incorrect, end of file reached" <<endl;
    }
	return 0;
} 






#endif
