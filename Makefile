all: pr_check

pr_check: courseNode.o pr_check.o
	g++ courseNode.o pr_check.o -o pr_check

courseNode.o: courseNode.cpp
	g++ -c courseNode.cpp courseNode.h

pr_check.o: pr_check.cpp
	g++ -c pr_check.cpp

clean:
	rm -f *.o *.h.gch pr_check