#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<string, courseNode> readPrerequisites(string filename)
{
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {

    }
}    

int main(int argc, char *argv[])
{
    string prereqfile = argv[1];
    string schedulefile = argv[2];

    
}