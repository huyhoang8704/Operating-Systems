all:  calc.o logic.o
	gcc calc.o logic.o -o calc
calc.o: calc.c calc.h
	gcc -c calc.c
logic.o: logic.c calc.h
	gcc -c logic.c
clean: # remove all object files and the executable
	rm -f *.o calc

