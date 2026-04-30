int_rep:
	gcc -std=c2x -Wall -IInclude src/int_rep.c src/main.c -o int_rep

clean:
	rm -rf int_rep