all: main
main: main.o symbol_table.o
	gcc -o main main.o symbol_table.o
main.o: main.c
	gcc -c main.c
symbol_table.o: symbol_table.c
	gcc	-c symbol_table.c