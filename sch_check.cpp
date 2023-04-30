#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string prereqfile = argv[1];
    ifstream prereqs(prereqfile);
    unordered_map<string, vector<vector<string>>> prerequisites;
    string line;

    while (getline(prereqs, line))
    {
        vector<string> prereqVector;
        string course, prereq;

        if (line != "")
        {
            stringstream currentLine(line);
            currentLine >> course;
            if (!prerequisites.count(course))
            {
                prerequisites[course] = vector<vector<string>>();
            }

            while (currentLine >> prereq)
            {
                prereqVector.push_back(prereq);
            }
            prerequisites[course].push_back(prereqVector);
        }
    }

    string schedulefile = argv[2];
    ifstream schedule(schedulefile);
    unordered_set<string> courses;
    unordered_map<string, int> coursesPerSemester;
    unordered_map<string, string> courseSemester;

    while (getline(schedule, line))
    {
        if (line != "")
        {
            stringstream currentLine(line);
            string course, semester;
            currentLine >> course;

            if (courses.count(course))
            {
                cout << "Duplicate course" << endl;
            }
            else
            {
            
                bool allPrereqsTaken = true;
                for (const vector<string> &prereqVector : prerequisites[course])
                {
                    bool allPrereqsTakenInVector = false;
                    for (const string &prereq : prereqVector)
                    {
                        if (courses.count(prereq))
                        {
                            allPrereqsTakenInVector = true;
                            if (courseSemester[prereq] != semester) 
                            {
                                cout << course << " and " << prereq << " taken in the same semester" << endl;
                                allPrereqsTaken = false;
                                break;
                            }
                        }
                    }

                    if (!allPrereqsTakenInVector)
                    {
                        allPrereqsTaken = false;
                        for (const string &prereq : prereqVector)
                        {
                            if (!courses.count(prereq))
                            {
                                cout << course << " Prerequisite not taken: " << prereq << endl;
                            }
                        }
                        break;
                    }
                }

                if (allPrereqsTaken)
                {
                    courses.insert(course);
                }
            }

            currentLine >> semester;
            coursesPerSemester[semester]++;
            if (coursesPerSemester[semester] > 3)
            {
                cout << "more than 3 courses taken" << endl;
            }

            courseSemester[course] = semester;
        }
    }

    for (const auto &course : prerequisites)
    {
        cout << course.first << ": ";
        for (const auto &prerequisites_list : course.second)
        {
            cout << "[";
            for (const auto &prerequisite : prerequisites_list)
            {
                cout << prerequisite << " ";
            }
            cout << "]";
        }
        cout << endl;
    }

    return 0;
}
