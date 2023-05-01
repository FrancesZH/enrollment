#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void sortCourses(string input_file, string output_file)
{
    // Open input file and read lines
    ifstream input(input_file);
    vector<string> lines;
    string line;
    while (getline(input, line))
    {
        if (line != "")
            lines.push_back(line);
    }
    input.close();

    // Sort lines by year and season
    sort(lines.begin(), lines.end(),
         [](const string &a, const string &b)
         {
             string a_1 = a.substr(a.find(' ') + 1);
             string b_1 = b.substr(b.find(' ') + 1);
             //  cout << a << "---" << a_1 << "---" << (a_1.substr(0, 4)) << endl;
             int year_a = stoi(a_1.substr(0, 4));
             string season_a = a_1.substr(4);
             int year_b = stoi(b_1.substr(0, 4));
             string season_b = b_1.substr(4);

             if (year_a != year_b)
             {
                 return year_a < year_b;
             }
             else
             {
                 // Compare seasons based on alphabetical order
                 return season_a < season_b;
             }
         });

    // Write sorted lines to output file
    ofstream output(output_file);
    for (const auto &line : lines)
    {
        output << line << endl;
    }
    output.close();
}

bool schCheck(string prereqfile, string schedulefile, string sem = "null")
{
    // Read prerequisites file
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

            // Create new set for course if it doesn't exist
            if (!prerequisites.count(course))
            {
                prerequisites[course] = vector<vector<string>>();
            }

            // Add each prerequisite to the set for this course
            while (currentLine >> prereq)
            {
                prereqVector.push_back(prereq);
            }

            // Assign the vector of prerequisites to the key in the unordered_map
            prerequisites[course].push_back(prereqVector);
        }
    }

    // Read schedule file
    unordered_set<string> courses;
    unordered_map<string, int> coursesPerSemester;
    string sortedPrereqfile = "sortedPrereqfile.txt";
    sortCourses(schedulefile, sortedPrereqfile);
    ifstream schedule(sortedPrereqfile);

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
                // Check if all prerequisites have been taken
                bool allPrereqsTaken = true;
                for (const vector<string> &prereqVector : prerequisites[course])
                {
                    bool allPrereqsTakenInVector = false;
                    for (const string &prereq : prereqVector)
                    {
                        // cout << "debug:" << prereq << endl;
                        // cout << "---";
                        if (courses.count(prereq))
                        {

                            allPrereqsTakenInVector = true;
                            break;
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

    return true;
}