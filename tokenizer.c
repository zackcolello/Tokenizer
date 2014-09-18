/*
 * tokenizer.c
 * Written by Zack Colello and Anna Genke
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


int isDelimiter (char c, TokenizerT *tokenizer);
char *Translate (char *untranslated);
char *TrimBuffer (char *buffer);
char *TranslateHexString (char *HexString);

char *indexPointer; //to be used to track where tokens are in the second argument

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

	TokenizerT *temptok;

	int SeparatorSize = strlen(separators);
	int StringSize = strlen(ts); 
	
	temptok = malloc(sizeof(TokenizerT));
	temptok->delimiters = (char*) malloc(SeparatorSize +1);
	temptok->input = (char*) malloc(StringSize +1);
  
	strcpy(temptok->delimiters, separators);
	strcpy(temptok->input, ts);

		return temptok;
}

/*
 *  * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 *   * allocated memory that is part of the object being destroyed.
 *    *
 *     * You need to fill in this function as part of your implementation.
 *      */

void TKDestroy(TokenizerT *tk) {
	
	free(tk->delimiters);
	free(tk);

	tk->delimiters = NULL;
	tk = NULL;


}

/*
 * Translate takes in an untranslated text that may contain escape characters that need to be translated to ascii value.
 *This function returns a translated version of the string to be used by TKCreate.
 * */
char *Translate (char *untranslated){	

	unsigned char *buff, *translated;
	int i,k;
	i=0; //Index for untranslated string
	k=0; //Index for buffer string
	buff = (char*) malloc(1000);
	
	while (untranslated[i]!='\0'){ //Loop until end of untranslated string
		
		if (untranslated[i] == '\\'){ //Found backslash, check through list of known escape characters

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
					buff[k] = (char) 0x0b;
					break;
				}
				case 'b':
				{
					buff[k] = (char) 0x08;
					break;
				}
				case 'r':
				{
					buff[k] = (char) 0x0d;
					break;
				}
				case 'f':
				{
					buff[k] = (char) 0x0c;
					break;
				}
				case 'a':
				{
					buff[k] = (char) 0x07;
					break;
				}
				case '\\':
				{
					buff[k] = (char) 0x5c;
					break;
				}
				case '"':
				{
					buff[k] = (char) 0x22;
					break;	
				}
				default:
					buff[k] = untranslated[i+1];				
					break;
				}
				
				k+=1;
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

/*Function TranslateHexString takes in a string argument that may contain literal hex values (such as a new line character)
 * and replaces those hex characters with their ascii value (ex: [0x0a]) as a string. 
 *It then returns a call to TrimBuffer, passing the now translated string as an argument. 
 */

char *TranslateHexString (char *HexString){

	char* BigBuffer;
	BigBuffer = (char*) malloc(1000);

	int i, j;
	i = 0; //index for HexString
	j = 0; //index for BigBuffer

	while(HexString[i] != '\0'){	

		if(HexString[i] == (char) 0x0a){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = 'a';
			BigBuffer[j+5] = ']';
			j += 6;

		}else if(HexString[i] == (char) 0x09){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = '9';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x0b){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = 'b';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x08){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = '8';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x0d){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = 'd';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x0c){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = 'c';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x07){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '0';
			BigBuffer[j+4] = '7';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x5c){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '5';
			BigBuffer[j+4] = 'c';
			BigBuffer[j+5] = ']';
			j += 6;
		}else if(HexString[i] == (char) 0x22){
			BigBuffer[j] = '[';
			BigBuffer[j+1] = '0';
			BigBuffer[j+2] = 'x';
			BigBuffer[j+3] = '2';
			BigBuffer[j+4] = '2';
			BigBuffer[j+5] = ']';
			j += 6;
		}else{		//Value at HexString[i] was not an escape character, copy character to BigBuffer as normal
		
			BigBuffer[j] = HexString[i];
			j++;

		}

		i++;
	}


	return TrimBuffer(BigBuffer);

}


/*Function TrimBuffer takes in a character array that may contain extra space, and cuts out the extra space to ensure the 
 * string has no extra characters. TrimBuffer returns a char* of the newly trimmed input.
 */

char *TrimBuffer (char *buffer){

	int buffersize, i;
	i = 0;
	buffersize = strlen(buffer);
	char* trimmed;
	trimmed = (char*) malloc(buffersize +1);

	while(buffer[i] != '\0'){ //loop until end of buffer
		
		trimmed[i] = buffer[i];
		i++;

	}	

	trimmed[i] = '\0';

	return trimmed;

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
		b = isDelimiter(c, tk);	

		if(c == '\0'){
		
			BigBuffer[BBIndex] = '\0';
			indexPointer = '\0';			

			return TrimBuffer(BigBuffer);


		}

		if(b == 0){ //not delimiter, add to BigBuffer
			
			BigBuffer[BBIndex] = c;
			BBIndex++;

			
		}else{ //is delimiter, return now

			indexPointer = &tk->input[i+1];
			tk->input = indexPointer;
			BigBuffer[BBIndex] = '\0';
			
			return TrimBuffer(BigBuffer);
		}

	}


  return 0;
}


/* Function isDelimiter is used by main to check if a character in the second argument is a delimiter.
 * isDelimiter uses tokenizer's delimiters value to compare a character with those delimiter values.
 * It returns 1 if the character is in the delimiter string, and 0 otherwise.
 * */
int isDelimiter(char c, TokenizerT *tokenizer){

	int delimLength, i;

	delimLength = strlen(tokenizer->delimiters);
	
	for(i = 0; i<strlen(tokenizer->delimiters); i++){ //cycle through delimiters to check against c
		
	
		if(tokenizer->delimiters[i] == c)
		{
			return 1;	//character c is a delimiter, return 1 for true	
		}
	}

	return 0;	//character c was not found to be a delimiter. Return 0 for false

}


/*
 *  * main will have two string arguments (in argv[1] and argv[2]).
 *   * The first string contains the separator characters.
 *    * The second string contains the tokens.
 *     * Print out the tokens in the second string in left-to-right order.
 *      * Each token should be printed on a separate line.
 *       */

int main(int argc, char **argv) {
	
	TokenizerT *tokenizer;

	if (argc != 3){
		printf("Please enter two arguments after calling tokenizer: (1) delimiters (2) String to be tokenized.\n");
		return -1;
	}

	tokenizer = TKCreate(Translate(argv[1]), Translate(argv[2]));

	indexPointer = tokenizer->input; //indexPointer now holds the input string to be used in while loop
	char* String;

		while (indexPointer != '\0'){ //We traverse tokenizer.input with indexPointer as we call TKGetNextToken
	
			String = TranslateHexString(TKGetNextToken(tokenizer)); 

	
			if(strlen(String) > 0){ //ensure we do not print blank tokens
	
				printf("%s\n", String);
		
			}		
		
			free(String);
		}	

		TKDestroy(tokenizer);

  	return 0;
}
