#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
//
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
bool semesterCheck(string prerequistSemester, string courseSemester) // winter, spring, summer, fall
{
    int year1 = stoi(prerequistSemester.substr(0, 4));
    int year2 = stoi(courseSemester.substr(0, 4));
    string semester1 = prerequistSemester.substr(4);
    string semester2 = courseSemester.substr(4);
    if (year1 > year2)
    {
        return false;
    }
    else if (year1 < year2)
    {
        return true;
    }
    else if (year1 == year2)
    {
        if (semester1 == "Winter")
        {
            if (semester2 != "Winter")
                return true;
            return false;
        }
        else if (semester1 == "Spring")
        {
            if (semester2 == "Summer" || semester2 == "Fall")
                return true;
            return false;
        }
        else if (semester1 == "Summer")
        {
            if (semester2 == "Fall")
                return true;
            return false;
        }
        else if (semester1 == "Fall")
        {
            return false;
        }
    }
    return true;
}
bool scheduleFileCheck(string courseToCheck, string semesterToCheck, unordered_set<string> &courses, unordered_map<string, vector<vector<string>>> &prerequisites, unordered_map<string, int> &coursesPerSemester, unordered_map<string, string> &periods, string s = "null", string c = "null")
{
    periods.insert({courseToCheck, semesterToCheck});
    if (courses.count(courseToCheck))
    {
        cout << "Error: Duplicate courses: " << courseToCheck << endl;
        return false;
    }
    else
    {
        // Check if all prerequisites have been taken
        bool allPrereqsTaken = true;
        for (const vector<string> &prereqVector : prerequisites[courseToCheck])
        {
            bool allPrereqsTakenInVector = false;
            for (const string &prereq : prereqVector)
            {
                if (courses.count(prereq))
                {
                    // Check if prerequisite is being taken at the same time as current course
                    if (periods[prereq] == periods[courseToCheck])
                    {
                        cout << "Error: " << prereq << " is a prerequisite for " << courseToCheck << " and is being taken at the same time." << endl;
                        return false;
                    }
                    else if (courseToCheck == c)
                    {
                        if (s != "null" && !semesterCheck(periods[prereq], s))
                        {
                            cout << "Error:" << prereq << " was not taken before " << s << endl;
                            return false;
                        }
                    }

                    allPrereqsTakenInVector = true;
                }
            }
            if (!allPrereqsTakenInVector)
            {
                allPrereqsTaken = false;
                for (const string &prereq : prereqVector)
                {
                    if (!courses.count(prereq))
                    {
                        cout << "Error: " << courseToCheck << " Prerequisite not taken: " << prereq << endl;
                        return false;
                    }
                }
            }
        }
        if (allPrereqsTaken)
        {
            courses.insert(courseToCheck);
        }
    }
    coursesPerSemester[semesterToCheck]++;
    if (coursesPerSemester[semesterToCheck] > 3)
    {
        cout << "Error: More than 3 courses taken" << endl;
        return false;
    }
    return true;
}
bool schCheck(string prerequisitesFile, string scheduleFile, string sem = "null", string courseToTake = "null")
{
    // Read prerequisites file
    ifstream prereqs(prerequisitesFile);
    unordered_map<string, vector<vector<string>>> prerequisites;
    unordered_map<string, int> coursesPerSemester;
    unordered_map<string, string> periods;
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
    sort_courses_by_season(scheduleFile, scheduleFile);

    ifstream schedule(scheduleFile);
    string course, semester;

    while (getline(schedule, line))
    {
        if (line != "")
        {
            stringstream currentLine(line);
            currentLine >> course >> semester;
            if (!scheduleFileCheck(course, semester, courses, prerequisites, coursesPerSemester, periods, sem, courseToTake))
                return false;
        }
    }
    if (courseToTake != "null" && !courses.count(courseToTake))
    {
        course = courseToTake;
        semester = sem;
        if (!scheduleFileCheck(course, semester, courses, prerequisites, coursesPerSemester, periods, sem, courseToTake))
            return false;
    }
    return true;
}

// for (const auto &course : prerequisites)
// {
//     cout << course.first << ": ";
//     for (const auto &prerequisites_list : course.second)
//     {
//         cout << "[";
//         for (const auto &prerequisite : prerequisites_list)
//         {
//             cout << prerequisite << " ";
//         }
//         cout << "]";
//     }
//     cout << endl;
// }