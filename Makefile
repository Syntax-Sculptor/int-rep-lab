int_rep:
	gcc -std=c2x -Wall -I include src/int_rep.c src/main.c -o int_rep

test:
	gcc -std=c2x -Wall -I include tests/test_int_rep.c src/int_rep.c -o test_int_rep

clean:
	rm -rf int_rep int_rep_test