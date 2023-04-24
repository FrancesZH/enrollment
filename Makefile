all: course

course: main.o
	g++ main.o -o course

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o *.h.gch course