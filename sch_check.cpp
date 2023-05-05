#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "schCheck.cpp"
using namespace std;

int main(int argc, char *argv[])
{
    string prereqfile = argv[1];
    string schedulefile = argv[2];

    schCheck(prereqfile, schedulefile);
    return 0;
}