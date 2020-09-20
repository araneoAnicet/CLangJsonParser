all: json.o main.o
	clang -std=gnu99 json.o main.o -o JsonParser

test: test.o json.o
	clang -std=gnu99 test.o json.o -o test

test.o: test.c
	clang -c test.c

main.o: main.c
	clang -c main.c

json.o: json.c
	clang -c json.c