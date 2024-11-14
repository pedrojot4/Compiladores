%{
// Reconhecedor de uma linguagem simplificada
#include <iostream>
#include "tokens.h"
using std::cout;
%}

%option noyywrap
delim	[ \t\n]
brancos {delim}+
letra	[A-Za-z]
digito	[0-9]
id	    {letra}({letra}|{digito})*
string   \"[A-Za-z0-9_,\\ \t/]*\"
num	    {digito}+(\.{digito}+)?(E[+-]?{digito}+)?


%%
{brancos}	; // nenhuma ação e nenhum retorno
if		    return IF; 
then		return THEN; 
else		return ELSE;
while       return WHILE; 
{id}		return ID;
{string}    return STRING;  
{num}	    return NUM; 
"<"		    return RELOP; 
"<="		return RELOP;
"!="		return RELOP;
"=="		return RELOP; 
"="		    return RELOP; 
"<>"		return RELOP; 
">"		    return RELOP;
">="		return RELOP; 
.           cout << YYText() << " é um token inválido!\n"; 
%%

// nenhuma função auxiliar é necessária
