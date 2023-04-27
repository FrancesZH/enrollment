#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

// unordered_map<string, courseNode> readPrerequisites(string filename)
// {
//     //I think is might just be same as Prere Check
//     ifstream infile(filename);
//     string line;
//     while (getline(infile, line))
//     {
//         stringstream ss(line);
//         string id, word;
//     }
// }

// //use to check the schedule
// bool CheckSchedule()
// {
//     bool valid = false;

//     /*
//         Schedule includes the same course more than once
//         Schedule proposes to take a course before its prerequisite
//         Schedule proposes too many courses (more than 3) in a semester
//     */

//     return valid ;
// }

int main(int argc, char *argv[])
{
    string prereqfile = argv[1];
    string schedulefile = argv[2];
}