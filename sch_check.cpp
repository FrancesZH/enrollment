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
    string prereqfile = argv[1];
    string schedulefile = argv[2];
    ifstream schedule(schedulefile);
    string line;
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
                courses.insert(course);
            currentLine >> semester;
            coursesPerSemester[semester]++;
            if (coursesPerSemester[semester] > 3)
                cout << "more than 3 course are taken" << endl;
            cout << coursesPerSemester[semester] << endl;
        }
    }
}
