#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "prCheck.cpp"
#include "schCheck.cpp"

using namespace std;

struct student
{
  string BNumber;
  int priority;
};

//---------------------------------------------------------

void MaxHeapPercolateDown(int nodeIndex, vector<student> &tree, int size)
{
  int childIndex = 2 * nodeIndex + 1;
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
        maxIndex = i + childIndex;
      }
    }

    if (maxValue == value)
    {
      return;
    }
    else
    {
      swap(tree[nodeIndex], tree[maxIndex]);
      nodeIndex = maxIndex;
      childIndex = 2 * nodeIndex + 1;
    }
  }
}

void Heapsort(vector<student> &tree)
{
  // Heapify the vector
  for (int i = tree.size() / 2 - 1; i >= 0; i--)
  {
    MaxHeapPercolateDown(i, tree, tree.size());
  }

  for (int i = tree.size() - 1; i > 0; i--)
  {
    swap(tree[0], tree[i]);
    MaxHeapPercolateDown(0, tree, i);
  }
}

student search(vector<student> &tree, string bnumber)
{
  for (int i = 0; i < tree.size(); i++)
  {
    if (tree[i].BNumber == bnumber)
    {
      return tree[i];
    }
  }
  // if student not found, return a default student object
  return student{"", 0};
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

  if (index == -1)
  {
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

void readin(string filename, vector<student> &MaxHeap, unordered_map<string, vector<student>> &waitlist)
{
  ifstream infile(filename);
  string line;

  while (getline(infile, line))
  {
    if (line != "")
    {
      stringstream ss(line);
      string command;
      ss >> command;

      // Read in the first "word" to check which function have to use
      if (command == "newlist")
      {
        string CourseName;
        ss >> CourseName;

        // create a waitlist with default student
        waitlist[CourseName] = vector<student>();
      }
      else if (command == "add")
      {
        string BNum, CourseName;
        int priority;

        ss >> BNum >> CourseName >> priority;

        // create student with BNum and priority point, put them in heap
        student s;
        s.BNumber = BNum;
        s.priority = priority;

        MaxHeap.push_back(s);

        waitlist[CourseName].push_back(s);
      }
      else if (command == "promote")
      {
        string BNum, CourseName;
        int priority;

        ss >> BNum >> CourseName >> priority;

        // find the student
        student temp = search(MaxHeap, BNum);

        // store student's priority point
        int temp_priority = temp.priority;

        remove_student(MaxHeap, BNum);

        temp.priority = temp_priority + priority;

        // Insert the student back in the heap
        MaxHeap.push_back(temp);
        Heapsort(MaxHeap);
      }
      else if (command == "enroll")
      {
        string CourseName;
        ss >> CourseName;
        student s;

        if (waitlist[CourseName].empty())
        {
          cout << "No students waiting for course " << CourseName << endl;
        }
        else
        {
          s = MaxHeap.back();
          MaxHeap.pop_back();

          cout << "Enrolling studeng " << s.BNumber << " in course " << CourseName << endl;
        }

        // loop over alll the course and set the student's pirority to 0
        for (auto &[course, students] : waitlist)
        {
          for (auto &student : students)
          {
            if (student.BNumber == s.BNumber)
            {
              student.priority = 0;
            }
          }
        }
      }
    }
  }
}

//---------------------------------------------------------

int main(int argc, char *argv[])
{
  //./waitlist 2023Fall prerequisites.txt schedules.txt enroll.txt
  // create a heap of student
  vector<student> MaxHeap;
  // create a list of course with list of students
  unordered_map<string, vector<student>> waitlist;

  string semester = argv[1];
  string prereqfile = argv[2];
  string schedsfile = argv[3];
  string enrollmentfile = argv[4];
  if (prCheck(prereqfile)) // check whether the prereqfile viable
    readin(enrollmentfile, MaxHeap, waitlist);
}