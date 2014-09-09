tokenizer: tokenizer.o
	gcc -Wall -o tokenizer tokenizer.o

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
