all: course

course: courseNode.o main.o
	g++ courseNode.o main.o -o course

courseNode.o: courseNode.cpp
	g++ -c courseNode.cpp courseNode.h

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o *.h.gch course