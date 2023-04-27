#include <iostream>
#include <string>
#include <vector>
using namespace std;

class courseNode
{
public:
    string courseName;
    string semID;
    int level;
    vector<vector<string>> prereq;
    courseNode(string courseName);
    courseNode();

    void addPrereq(vector<string> prereqVector);
};

