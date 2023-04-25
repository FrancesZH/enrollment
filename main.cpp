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
        // vector<courseNode> prereq;
        cout << "\nid:" << id << "\tprereq:";
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
            cout << word << " ";
            courseNode pre_obj = courseNode(word);
            obj.addPrereq(&pre_obj);
            cout << "len=" << obj.prereq.size() << endl;
            course_id.emplace(word, pre_obj);
            // prereq.push_back(pre_obj);
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
        cout << node.courseName << " " << node.prereq.size() << endl;
        // if (node.prereq[0] != nullptr)
        // {
        //     cout << node.prereq[0]->courseName << "\n";
        // }
    }
    return 0;
}

