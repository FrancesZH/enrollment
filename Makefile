all: course

course: prereq.o main.o
	g++ prereq.o main.o -o course

prereq.o: prereq.cpp
	g++ -c prereq.cpp prereq.h

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o *.h.gch course