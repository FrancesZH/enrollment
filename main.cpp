#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

set<string> CourseID(string filename)
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
    set<string> course_id = CourseID(filename);
    for (string id : course_id)
    {
        cout << id << endl;
    }
    return 0;
}
