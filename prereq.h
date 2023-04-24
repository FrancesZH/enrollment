#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    string ID;
    vector<int> edges;
    Node(string ID);
};

class Graph
{
public:
    vector<Node *> nodes;

    void addNode(string ID);
    void addEdge(string coursid, string prerqid);
    void printGraph();
};

