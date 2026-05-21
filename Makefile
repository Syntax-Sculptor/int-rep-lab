

int_rep:
	mkdir -p build
	gcc -std=c2x -Wall -I include src/int_rep.c src/main.c -o build/int_rep

test:
	mkdir -p build
	gcc -std=c2x -Wall -I include tests/test_int_rep.c src/int_rep.c -o build/test_int_rep

clean:
	rm -rf build