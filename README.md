Once upon a time, there was a perfectly good Computer Science Department that destroyed everything by selecting the wrong Undergraduate Director. Without rehashing the details of the disaster, suffice it to say that the department is in the early stages of building some automation into the system, and you have been selected to help.

Prerequisite Checker

Your first task is to write a program that reads in prerequisite information from a file, and checks that it is possible for students to take all 200 level and 300 level courses that are listed, while meeting prerequisites for each one. If Course A is a prerequisite for Course B, then it must be taken before B can be taken. Students must be able to take all the 200-300 level courses within 6 semesters (leaving senior year for 400 level electives, which may be taken only after all 200 and 300 level courses are taken).

Prerequisites will be read from a file whose format is implied by the following example:

CS_120 CS_110
CS_210 CS_120
CS_310 CS_120
CS_375 CS_310
CS_375 MATH_314 MATH_330

Classes are formatted as <dept>_<ddd>, where <dept> is 2 to 4 characters and <ddd> is the course number and always 3 digits.

The first line indicates that CS_110 is a prerequisite for CS_120. The last two lines indicate that MATH_314 or MATH_330 must be taken before CS_375, and CS_310 must also be taken before CS_375.

Given a well-formatted file with these prerequisites listed, your program pr_check should output whether the set of prerequisites is "viable" or "not viable".  If it is not viable, your program should report why it is not---either because the prerequisites have circular dependencies (you should output what that dependency is) or there is a sequence of necessary prerequisites that exceeds 6, and so the courses cannot be taken within 6 semesters.

You will be given a sample executable that exhibits the format of pr_check's output, which will be confined to exactly one line. Your program should read the name of the file from the one and only command line argument:
./pr_check <prereqfile>

For example, 
./pr_check prereqs.txt

Schedule Checker

The next program you write should be called sch_check, should be invoked with two parameters (the name of a prerequisite file and the name of a schedule file), and should check the viability of a student's proposed schedule.
./sch_check <prereqfile> <schedulefile>

For example, 
./sch_check prereqfile.txt schedfile.txt

The format of the prerequisites file is the same as above, and the format of the schedule file, by example, is:
CS_110 2021Fall
CS_120 2022Spring
CS_210 2022Fall
CS_310 2023Spring
CS_320 2023Spring
CS_375 2023Fall
CS_373 2023Fall
CS_350 2024Spring

The lines indicate the courses that the student intends to take, and the semesters in which they were or will be taken. Input lines may appear in any order; they will not necessarily be chronological. If a course has no prerequisites, you may assume that it is OK to take. Semesters are well formed strings of the form: <yyyy><semester>, where <semester> may be Spring, Summer, or Fall.

The following errors in the schedule should be noticed and flagged, exactly as the sample executable will.  (One output message per line, per error... your program needs to report only the first error it notices; if there are multiple errors, noticing any one of them is considered correct behavior for your program.)

Schedule includes the same course more than once
Schedule proposes to take a course before its prerequisite
Schedule proposes too many courses (more than 3) in a semester
The file may contain information about past semesters, and potentially multiple future semesters. It doesn't matter what "moment" it is at the time the program runs. If there are errors in the "schedule" for past semesters, one of them should be flagged. If there are errors in future semesters, one of them should be flagged.

Waitlist

The third program you should implement, is waitlist. Input comes in three files, a prerequisites file, a schedules file and an enrollment file.  Thus, the program should be invoked as follows:
./waitlist <semester> <prereqfile> <schedsfile> <enrollmentfile>

For example,
./waitlist 2023Fall prerequisites.txt schedules.txt enroll.txt

The <semester> parameter is a semester string formatted as described for the schedule file, above.

The prerequisites file is formatted as described in the Prerequisite Checker section above. 

The schedules file format, by example, is as follows:

B00112233 b00112233.txt
B00445566 SanjeevSchedule.txt

This file indicates that we have schedules for two students, with the indicated B numbers. The two students' schedules are in files b00112233.txt and SanjeevSchedule.txt. Those files are formatted as described in the Schedule Checker section above.

The enrollment file has the following format, by example:

newlist CS_310
add B00112233 CS_310 10
add B00445566 CS_310 20
promote B00112233 CS_310 20
enroll CS_310

This sample file creates a new waitlist for CS_310 on the first line, adds two students to that list, with 10 and 20 "priority points" respectively, then adds 20 priority points to the first student, and finally enrolls the student with the most points from the CS_310 waitlist in the course. When a student is taken off the waitlist for a course, they should lose all priority points for other courses, but should remain in the waitlists.

To "enroll" a student, you need only print the following line:

Enrolling student B00112233 in course CS_310

Your program, called waitlist, takes the names of input file as parameters, along with the current semester, and prints which students get enrolled in which courses, in order. If the prerequisites file contains an error, that should be reported and your waitlist program should halt. If any student's schedule contains an error, that should be reported and your program should halt.
