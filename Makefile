all: pr_check sch_check waitlist

pr_check: courseNode.o pr_check.o
	g++ courseNode.o pr_check.o -o pr_check

sch_check: courseNode.o sch_check.o
	g++ courseNode.o sch_check.o -o sch_check

waitlist: courseNode.o waitlist.o
	g++ courseNode.o waitlist.o -o waitlist

courseNode.o: courseNode.cpp courseNode.h
	g++ -c courseNode.cpp

pr_check.o: pr_check.cpp courseNode.h
	g++ -c pr_check.cpp

sch_check.o: sch_check.cpp courseNode.h
	g++ -c sch_check.cpp

waitlist.o: waitlist.cpp courseNode.h
	g++ -c waitlist.cpp

clean:
	rm -f *.o *.h.gch pr_check sch_check waitlist