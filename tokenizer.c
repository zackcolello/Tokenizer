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
 
	delims = (char*) malloc(SeparatorSize +1);
	string = (char*) malloc(StringSize +1);

	strcpy(delims, separators);
	strcpy(string, ts);

	//tokenizer.delimiters = delims;
	//tokenizer.input = string;
	tokenizer.delimiters = (delims);
	tokenizer.input = (string);

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

	unsigned char *buff, *translated;
	int i,k;
	i=0;
	k=0;
	buff = (char*) malloc(1000);
	
	while (untranslated[i]!='\0'){
		
		if (untranslated[i] == '\\'){

			switch (untranslated[i+1]){
			
				case 'n':
				{
					buff[k] = (char) 0x0a;
					break;
				}
				case 't':
				{
					buff[k] =(char) 0x09;
					break;
				}
				case 'v':
				{
					buff[k] = 0x0b;
					break;
				}
				case 'b':
				{
					buff[k] = 0x08;
					break;
				}
				case 'r':
				{
					buff[k] = 0x0d;
					break;
				}
				case 'f':
				{
					buff[k] = 0x0c;
					break;
				}
				case 'a':
				{
					buff[k] = 0x07;
					break;
				}
				case '\\':
				{
					buff[k] = 0x5c;
					break;
				}
				case '"':
				{
					buff[k] = 0x22;
				
				}
					break;
				}
	
				k+=2;
				i+=2;

			}else{
	
			buff[k]=untranslated[i];
			k++;
			i++;
			}

		}

		buff[k+1] = '\0';

		translated = buff;

	return translated;


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
	
	int i, b, BBIndex;
	BBIndex = 0;

	char c;
	char* BigBuffer; //to be used for returning tokens
	BigBuffer = (char*) malloc(1000);
	

	for(i = 0; i<(strlen(indexPointer)+1); i++){

	
		c = (indexPointer[i]);
		b = isDelimiter(c);	

		if(c == '\0'){
		
			BigBuffer[BBIndex] = '\0';
			
			//indexPointer = BigBuffer[BBIndex];
			indexPointer = '\0';			

			//tokenizer.input = indexPointer;	

			return BigBuffer;

		}

		if(b == 0){ //not delimiter, add to BigBuffer
			
			//if(c != '\\'){ //skip over "\"
			BigBuffer[BBIndex] = c;
			BBIndex++;
			//}

			
		}else{ //is delimiter, return now

			
			indexPointer = &tokenizer.input[i+1];
			tokenizer.input = indexPointer;
			BigBuffer[BBIndex] = '\0';
	
	
			return BigBuffer;
		}

	}


  return NULL;
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
		
	
		if(tokenizer.delimiters[i] == c)
		{
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


	TKCreate(Translate(argv[1]), Translate(argv[2]));

	//TKCreate(argv[1], argv[2]);


	indexPointer = tokenizer.input;
	char* String;

	printf("%s\n", tokenizer.input);

	while (indexPointer != '\0'){ //we decrease tokenizer.input as we call tkgetNextToken
	
		String = TKGetNextToken(&tokenizer); 
	
		if(strlen(String) > 0){
	
			printf("'%s'\n", String);
		
		}		
//		free(String);
	}

  return 0;
}
