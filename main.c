#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>


/* Variáveis */
int charClass;
char lexeme[100];
char nextChar;
int lexLenght;
int token;
int nextToken;
FILE  *in_fp, *fopen();


/* Funções */
void addChar();
void getChar(); //obtém o próximo caractere de entradado programa e o coloca na variável nextChar
void getNonBlank();
int lex();

/* Classe de caracteres */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Códigos de tokens */
#define FALSE 0
#define TRUE 1
#define INT_LIT 10
#define IDENT 11
#define OR_OP 20
#define AND_OP 21
#define NOT_OP 22
#define IMPLIES_OP 23
#define BIIMPLIES_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int main(void){
	in_fp = fopen("entrada.in", "r");
	if (in_fp == NULL)
       printf("ERROR - cannot open entrada.in \n");
    else {
    	getChar();
    	do{
    		lex();
		}while(nextToken != EOF);
	}
}

/*função para processar operadores e parênteses e retornar o token */
int lookup(char ch){
	switch(ch){
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		case '+':
			addChar();
			nextToken = OR_OP;
			break;
		case '*':
			addChar();
			nextToken = AND_OP;
			break;
		case '!':
			addChar();
			nextToken = NOT_OP;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	
	return nextToken;
}

/* Função para adicionar nextChar ao vetor lexeme */
void addChar(){
	if(lexLenght <= 98){
		lexeme[lexLenght++] = nextChar;
		lexeme[lexLenght] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

/* função para obter o próximo caractere da entrada e determinar sua classe de caracteres */
void getChar(){
	if ((nextChar = getc(in_fp)) != EOF) {
    	if (isalpha(nextChar))
    	charClass = LETTER;
    	else if (isdigit(nextChar))
			charClass = DIGIT;
		else 
			charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

/* Função para chamar getChar até que ela retorne um caractere diferente de espaço em branco */
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

int lex() {
	lexLenght = 0;
	getNonBlank();
	switch (charClass) {
		/* Reconhecer identificadores */
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		/* Reconhecer literais inteiros */
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		/* Parênteses e operadores */
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		/* Fim do arquivo */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	}
	printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	return nextToken;
} 





