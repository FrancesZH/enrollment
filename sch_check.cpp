#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[])
{
    // Read prerequisites file
    string prereqfile = argv[1];
    ifstream prereqs(prereqfile);
    unordered_map<string, unordered_set<string>> prerequisites;

    string line;
    while (getline(prereqs, line))
    {
        if (line != "")
        {
            stringstream currentLine(line);
            string course, prereq;
            currentLine >> course;

            // Create new set for course if it doesn't exist
            if (!prerequisites.count(course))
                prerequisites[course] = unordered_set<string>();

            // Add each prerequisite to the set for this course
            while (currentLine >> prereq)
                prerequisites[course].insert(prereq);
        }
    }

    // Read schedule file
    string schedulefile = argv[2];
    ifstream schedule(schedulefile);
    unordered_set<string> courses;
    unordered_map<string, int> coursesPerSemester;

    while (getline(schedule, line))
    {
        if (line != "")
        {
            stringstream currentLine(line);
            string course, semester;
            currentLine >> course;
            if (courses.count(course))
                cout << "Duplicate course" << endl;
            else
            {
                // Check if all prerequisites have been taken
                bool allPrereqsTaken = true;
                for (string prereq : prerequisites[course])
                {
                    if (!courses.count(prereq))
                    {
                        allPrereqsTaken = false;
                        cout << course <<" "<< "Prerequisite not taken: " << prereq << endl;
                    }
                }

                if (allPrereqsTaken)
                    courses.insert(course);
            }

            currentLine >> semester;
            coursesPerSemester[semester]++;
            if (coursesPerSemester[semester] > 3)
                cout << "more than 3 courses taken" << endl;
            cout << coursesPerSemester[semester] << endl;
        }
    }
}
