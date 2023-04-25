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

void courseNode::addPrereq(courseNode *node)
{
    cout << "push";
    prereq.push_back(node);
}