/*
 * tokenizer.c
 * testestest hello world
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDelimiter (char c);
char *Translate (char *untranslated);
char *indexPointer; //to be used to track where tokens are in the second argument


/*
 *  * Tokenizer type.  You need to fill in the type as part of your implementation.
 *   */


struct TokenizerT_ {

char* delimiters;
char* input; 
};

typedef struct TokenizerT_ TokenizerT;


TokenizerT tokenizer;

/*
 *  * TKCreate creates a new TokenizerT object for a given set of separator
 *   * characters (given as a string) and a token stream (given as a string).
 *    * 
 *     * TKCreate should copy the two arguments so that it is not dependent on
 *      * them staying immutable after returning.  (In the future, this may change
 *       * to increase efficiency.)
 *        *
 *         * If the function succeeds, it returns a non-NULL TokenizerT.
 *          * Else it returns NULL.
 *           *
 *            * You need to fill in this function as part of your implementation.
 *             */

 *TKCreate(char *separators, char *ts) {

	int SeparatorSize = strlen(separators);
	int StringSize = strlen(ts); 
  
	char* delims, *string;
 
	delims = malloc(SeparatorSize +1);
	string = malloc(StringSize +1);

	strcpy(delims, separators);
	strcpy(string, ts);



	tokenizer.delimiters = Translate(delims);
	tokenizer.input = Translate(string);

	
//	printf("tokenizer delim is %s, and tokenizer input is %s\n", tokenizer.delimiters, tokenizer.input);

		return &tokenizer;
}

/*
 *  * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 *   * allocated memory that is part of the object being destroyed.
 *    *
 *     * You need to fill in this function as part of your implementation.
 *      */

void TKDestroy(TokenizerT *tk) {
}

/*
 * Translate takes in an untranslated text that may contain escape characters that need to be translated to ascii value.
 *This function returns a translated version of the string to be used by TKCreate.
 * */
char *Translate (char *untranslated){	


	return untranslated;	

}
/*
 *  * TKGetNextToken returns the next token from the token stream as a
 *   * character string.  Space for the returned token should be dynamically
 *    * allocated.  The caller is responsible for freeing the space once it is
 *     * no longer needed.
 *      *
 *       * If the function succeeds, it returns a C string (delimited by '\0')
 *        * containing the token.  Else it returns 0.
 *         *
 *          * You need to fill in this function as part of your implementation.
 *           */

char *TKGetNextToken(TokenizerT *tk) {
	
	int i, b;

	char c;
	char* BigBuffer; //to be used for returning tokens
	BigBuffer = malloc(1000);
	

	for(i = 0; i<strlen(tokenizer.input); i++){
	
		c = (tokenizer.input[i]);
		b = isDelimiter(c);	//isDelimiter is now working yay!

		printf("Just compared %c and delimiters.\n", c);
		printf("boole is %d\n", b);

//		if(b == 0){ //not delimiter, add to BigBuffer
		
//		}

//		printf("%c\n", tokenizer.input[i]);
	
	}


  return tokenizer.input;
}


/* Function isDelimiter is used by main to check if a character in the second argument is a delimiter.
 * isDelimiter uses tokenizer's delimiters value to compare a character with those delimitervalues.
 * It returns 1 if the character is in the delimiter string, and 0 otherwise.
 * */
int isDelimiter(char c){

	int delimLength, i;
	float boole;

	delimLength = strlen(tokenizer.delimiters);

	for(i = 0; i<strlen(tokenizer.delimiters); i++){ //cycle through delimiters to check against c
		
		boole = strcmp(&tokenizer.delimiters[i], &c);
		
		//printf("now comparing %c and %c\n", tokenizer.delimiters[i], c);
		//printf("boole is %d\n", boole);
	
		if(boole == 0){

			return 1;	
		}
	}

	return 0;

}


/*
 *  * main will have two string arguments (in argv[1] and argv[2]).
 *   * The first string contains the separator characters.
 *    * The second string contains the tokens.
 *     * Print out the tokens in the second string in left-to-right order.
 *      * Each token should be printed on a separate line.
 *       */

int main(int argc, char **argv) {


	if (argc != 3){
		printf("please enter two arguments after calling tokinizer: (1) delimiters (2) String to be tokenized.\n");
		return -1;
	}


	TKCreate(argv[1], argv[2]);

	indexPointer = tokenizer.input;
	char* String;


	while (strlen(tokenizer.input) !=0){ //we decrease tokenizer.input as we call tkgetNextToken
	
		String = TKGetNextToken(&tokenizer); //unsure why & makes all these work, does not work without it
	
		printf("%s\n", String);
		
		break;//adding this here because I'm still working on how to properly end this loop
	}

  return 0;
}
