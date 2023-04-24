#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "prereq.h"

using namespace std;

set<string> ReadCourses(string filename)
{
    set<string> course_id;
    ifstream infile(filename);
    string id;
    while (infile >> id)
    {
        course_id.insert(id);
    }
    infile.close();
    return course_id;
}

int main()
{
    string filename = "courses.txt";
    set<string> course_id = ReadCourses(filename);
    for (string id : course_id)
    {
        cout << id << endl;
    }
    
}
