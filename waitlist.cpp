#include <iostream>
using namespace std;

struct student
{
    String BNumber; 
    int priority; 
};

//---------------------------------------------------------

void MaxHeapPercolateDown(int nodeIndex, vector<student> &tree, int size) {
   int childIndex = 2 * nodeIndex + 1 ; 
   int value = tree[nodeIndex].priority;

   while (childIndex < size)
    {
      // Find the max among the node and all the node's children
      int maxValue = value;
      int maxIndex = -1;

      for (int i = 0; i < 2 && i + childIndex < size; i++) 
      {
        if (tree[i + childIndex].priority > maxValue)
        {
            maxValue = tree[i + childIndex].priority;
            maxIndex = i + childIndex ;
        }
      }

      if (maxValue == value) 
      {
        return;
      }
      else 
      {
        swap(tree[nodeIndex], tree[maxIndex]);
        nodeIndex = maxIndex ; 
        childIndex = 2 * nodeIndex + 1 ; 
      }
   }
}

void Heapsort(vector<student> &tree) 
{
   // Heapify the vector
   for (int i = tree.size() / 2 - 1; i >= 0; i--) {
      MaxHeapPercolateDown(i, tree, tree.size());
   }

   for (int i = tree.size() - 1; i > 0; i--) {
      swap(tree[0], tree[i]);
      MaxHeapPercolateDown(0, tree,i);
   }
}

void remove_student(vector<student> &tree, string bnumber) 
{   
    // search inside the tree to see if student exist
    int index = -1;
    for (int i = 0; i < tree.size(); i++) 
    {
        if (tree[i].BNumber == bnumber)
        {
            index = i;
            break;
        }
    }

    if (index == -1) {
        // student not found in heap
        return;
    }

    // replace the student to be removed with the last element in the heap
    tree[index] = tree[tree.size() - 1];

    // remove the last element from the heap
    tree.pop_back();

    Heapsort(tree);
}

//---------------------------------------------------------

int main(int argc, char *argv[])
{
    string semester = argv[1];
    string prereqfile = argv[2];
    string schedsfile = argv[3];
    string enrollmentfile = argv[4];
}