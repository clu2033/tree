compile:
	g++ -g -Wall -std=c++14 -g -O0 -pedantic-errors -o Driver Driver.cpp TreeType.cpp QueType.cpp 

run: 
	./Driver

clean:
	rm -f Driver
	rm -f *.o
