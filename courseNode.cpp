#include <iostream>
#include <string>
#include <vector>
#include "courseNode.h"
using namespace std;

courseNode::courseNode(string courseName)
{
    this->courseName = courseName;
}
courseNode::courseNode()
{
}

void courseNode::addPrereq(vector<string> prereqVector)
{
    // cout << "push";
    prereq.push_back(prereqVector);
}
// void courseNode::addPrereq(vector prereqVector)
// {
//     // cout << "push";
//     prereqVector.push_back(prereqVector);
// }