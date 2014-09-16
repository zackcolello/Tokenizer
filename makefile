tokenizer: tokenizer.o
	gcc -g -Wall -o tokenizer tokenizer.o

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
