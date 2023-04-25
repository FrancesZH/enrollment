#include <iostream>
#include <vector>
#include "prereq.h"
using namespace std;

Node::Node(string ID)
{
    this->ID = ID;
}

void Graph::addNode(string ID)
{
    Node *newNode = new Node(ID);
    nodes.push_back(newNode);
}

void Graph::addEdge(string coursid, string prerqid)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        Node *node = nodes[i];
        if (node->ID == coursid)
        {
            int edge = stoi(prerqid);
            node->edges.push_back(edge);
            return;
        }
    }
}

void Graph::printGraph()
{
    for (Node *node : nodes)
    {
        cout << node->ID << " -> ";
        for (int edge : node->edges)
        {
            Node *prereq = nodes[edge];
            cout << prereq->ID << " ";
        }
        cout << endl;
    }
}
