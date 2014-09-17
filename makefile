all: main
main: main.o Date.o Course.o Section.o
	g++ main.o Date.o Course.o Section.o -Wall -g -o main
main.o: main.cpp
	g++ -Wall -g -c main.cpp
Date.o: Date.cpp Date.h
	g++ -Wall -g -c Date.cpp Date.h
Course.o: Course.cpp Course.h Section.h 
	g++ -Wall -g -c Course.cpp Course.h Section.h
Section.o: Section.cpp Section.h Course.h Date.h
	g++ -Wall -g -c Section.cpp Section.h Course.h Date.h
clean:
	rm -f *.o *.gch main
