/*
 * tokenizer.c
 * testestest hello world
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TokenizerT *TKCreate(char *separators, char *ts) {

	int SeparatorSize = strlen(separators);
	int StringSize = strlen(ts); 
  
	char* delims, *string;

	delims = malloc(SeparatorSize +1);
	string = malloc(StringSize +1);

	strcpy(delims, separators);
	strcpy(string, ts);

	printf("Delim is %s, and String is %s\n", delims, string);

	//TokenizerT.delimiters = malloc(SeparatorSize+1);
	//TokenizerT.input = malloc(StringSize +1);

  
	tokenizer.delimiters = delims;
	tokenizer.input = string;
	
	printf("tokenizer delim is %s, and tokenizer input is %s\n", tokenizer.delimiters, tokenizer.input);

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




  return NULL;
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




	//printf("Global strang is now %s\n", GlobalString);




  return 0;
}
