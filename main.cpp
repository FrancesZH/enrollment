#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "courseNode.h"
#include <sstream>

using namespace std;

unordered_map<string, courseNode> ReadCourses(string filename)
{
    unordered_map<string, courseNode> course_id;
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {
        if (line != "")
        {
            stringstream ss(line);
            string id, word;
            ss >> id;
            bool isNew = true;
            auto foundObj = course_id.find(id);
            courseNode obj;
            if (foundObj != course_id.end())
            {
                obj = foundObj->second;
                isNew = false;
            }
            else
            {
                obj = courseNode(id);
            }

            while (ss >> word)
            {
                if (word == id)
                {
                    continue;
                }
                bool isAlreadyPrereq = false;
                for (auto const &prereq : obj.prereq)
                {
                    if (prereq->courseName == word)
                    {
                        isAlreadyPrereq = true;
                        break;
                    }
                }
                if (isAlreadyPrereq)
                {
                    continue; // skip adding already present prerequisite
                }
                courseNode *prereq_obj;
                auto foundPrereq = course_id.find(word);
                if (foundPrereq != course_id.end())
                {
                    prereq_obj = &(foundPrereq->second);
                }
                else
                {
                    prereq_obj = new courseNode(word);
                    course_id.emplace(word, *prereq_obj);
                }
                obj.addPrereq(prereq_obj);
            }
            if (isNew)
            {
                course_id.emplace(id, obj);
            }
            else
            {
                course_id[id] = obj;
            }
        }
    }
    infile.close();
    return course_id;
}
bool checkCircularDependencies(unordered_map<string, courseNode> courses, string currentCourse)
{
    // for (auto const &[id, course] : courses)
    // {
    // }
}
bool contain(unordered_map<string, courseNode> courses, string course1, string course2)
{
    // for (auto const &[id, node] : courses)
    // {
    //     if (courses->courseName)
    // }
}
int main(int argc, char *argv[])
{
    string filename = argv[1];
    unordered_map<string, courseNode> course_id = ReadCourses(filename);
    cout << "\n\n----------------\n\n";
    int prerequisitesCount = 0;
    for (auto const &[id, node] : course_id)
    {
        // cout << node.courseName << " " << node.prereq() << endl;
        // if (node.prereq[0] != nullptr)
        // {
        //     cout << node.prereq[0]->courseName << "\n";
        // }
        cout << node.courseName << " Prereq:";
        for (auto const &prereq : node.prereq)
        {
            cout << " " << prereq->courseName;
            prerequisitesCount++;
        }
        if (prerequisitesCount > 6)
            cout << "\nNot Viable: Exceeds 6 prerequisites";

        // cout << "\nNot Viable: prerequisites have circular dependencies";

        prerequisitesCount = 0;
        cout << endl;
    }
    return 0;
}
