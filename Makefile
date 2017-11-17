compile:
	g++ -g -Wall -std=c++14 -g -O0 -pedantic-errors -o TreeDr TreeDr.cpp TreeType.cpp QueType.cpp 

run: 
	./TreeDr

clean:
	rm -f TreeDr
	rm -f *.o
