#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    // Read prerequisites file
    string prereqfile = argv[1];
    ifstream prereqs(prereqfile);
    unordered_map<string, vector<vector<string>>> prerequisites;
    string line;

    while (getline(prereqs, line)) {
        vector<string> prereqVector;
        string course, prereq;

        if (line != "") {
            stringstream currentLine(line);
            currentLine >> course;

            // Create new set for course if it doesn't exist
            if (!prerequisites.count(course)) {
                prerequisites[course] = vector<vector<string>>();
            }

            // Add each prerequisite to the set for this course
            while (currentLine >> prereq) {
                prereqVector.push_back(prereq);
            }

            // Assign the vector of prerequisites to the key in the unordered_map
            prerequisites[course].push_back(prereqVector);
        }
    }

    // Read schedule file
    string schedulefile = argv[2];
    ifstream schedule(schedulefile);
    unordered_set<string> courses;
    unordered_map<string, int> coursesPerSemester;

    while (getline(schedule, line)) {
        if (line != "") {
            stringstream currentLine(line);
            string course, semester;
            currentLine >> course;

            if (courses.count(course)) {
                cout << "Duplicate course" << endl;
            } else {
                // Check if all prerequisites have been taken
                bool allPrereqsTaken = true;
                for (const vector<string>& prereqVector : prerequisites[course]) {
                    bool allPrereqsTakenInVector = false;
                    for (const string& prereq : prereqVector) {
                        if (courses.count(prereq)) {
                            allPrereqsTakenInVector = true;
                            break;
                        }
                    }

                    if (!allPrereqsTakenInVector) {
                        allPrereqsTaken = false;
                        cout << course << " Prerequisite not taken" << endl;
                        break;
                    }
                }

                if (allPrereqsTaken) {
                    courses.insert(course);
                }
            }

            currentLine >> semester;
            coursesPerSemester[semester]++;
            if (coursesPerSemester[semester] > 3) {
                cout << "more than 3 courses taken" << endl;
            }
        }
    }

    for (const auto& course : prerequisites) {
        cout << course.first << ": ";
        for (const auto& prerequisites_list : course.second) {
            cout << "[";
            for (const auto& prerequisite : prerequisites_list) {
                cout << prerequisite << " ";
            }
            cout << "]";
        }
        cout << endl;
    }

    return 0;
}
