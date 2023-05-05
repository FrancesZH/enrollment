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

courseNode::~courseNode()
{
    // delete courseName;
}

void courseNode::addPrereq(vector<string> prereqVector)
{
    prereq.push_back(prereqVector);
}