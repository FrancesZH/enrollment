#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void sort_courses_by_season(string input_file, string output_file)
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
bool semesterCheck(string sem1, string sem2)
{
    int year1 = stoi(sem1.substr(0, 4));
    int year2 = stoi(sem2.substr(0, 4));
    string semester1 = sem1.substr(4);
    string semester2 = sem2.substr(4);
    if (year1 >= year2)
    {
        return true;
    }
    else if (year1 < year2)
    {
        return false;
    }
    else
    {
        return semester1 > semester1;
    }
}

bool schCheck(string prerequisitesFile, string scheduleFile, string sem = "null", string courseToTake = "null")
{
    // Read prerequisites file
    ifstream prereqs(prerequisitesFile);
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
    sort_courses_by_season(scheduleFile, scheduleFile);
    unordered_map<string, string> periods;

    ifstream schedule(scheduleFile);

    while (getline(schedule, line))
    {
        if (line != "")
        {
            stringstream currentLine(line);
            string course, semester;
            currentLine >> course >> semester;
            periods.insert({course, semester});

            if (courses.count(course))
            {
                cout << "Duplicate course" << endl;
                return false;
            }
            else
            {
                // Check if all prerequisites have been taken
                bool allPrereqsTaken = true;
                for (const vector<string> &prereqVector : prerequisites[course])
                {
                    for (const string &prereq : prereqVector)
                    {
                        if (periods[prereq] >= sem)
                        {
                            cout << course << " prerequisites not taken before semester " << sem << endl;
                            return false;
                        }
                    }
                }
                for (const vector<string> &prereqVector : prerequisites[course])
                {
                    bool allPrereqsTakenInVector = false;
                    for (const string &prereq : prereqVector)
                    {
                        if (courses.count(prereq))
                        {
                            // Check if prerequisite is being taken at the same time as current course
                            if (periods[prereq] == periods[course])
                            {
                                cout << "Error: " << prereq << " is a prerequisite for " << course
                                     << " and is being taken at the same time." << endl;
                                return false;
                            }
                            if (course == courseToTake)
                            {
                                cout << course << " " << courseToTake << endl;

                                cout << "---------testing--------" << endl;
                                if (semester != "null" && !semesterCheck(sem, periods[prereq]))
                                {

                                    cout << courseToTake << " cannot be taken before its designated semester." << endl;
                                    return false;
                                }
                            }
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
                                return false;
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
            coursesPerSemester[semester]++;
            if (coursesPerSemester[semester] > 3)
            {
                cout << "more than 3 courses taken" << endl;
                return false;
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
