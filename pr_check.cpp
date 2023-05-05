#include <iostream>
#include <fstream>
#include <string>
#include "prCheck.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[1];
    prCheck(filename);
    return 0;
}
