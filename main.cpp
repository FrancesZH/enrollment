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
            courseNode* prereq_obj;
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
    infile.close();
    return course_id;
}


int main()
{
    string filename = "courses.txt";
    unordered_map<string, courseNode> course_id = ReadCourses(filename);
    cout << "\n\n----------------\n\n";
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
        }
        cout << endl;
    }
    return 0;
}
