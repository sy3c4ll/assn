#pragma once
#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 100

struct pq_element
{
    int priority;
    int value;
};

class PriorityQueue
{
private:
    pq_element heap[MAX_SIZE];
    int size;
    /* BEGIN_YOUR_CODE */

    /* END_YOUR_CODE */

public:
    PriorityQueue()
    {
        size = 0;
    }

    bool insert(int priority, int value); // insert element

    bool removeMax(); // remove a pq_element having maximum priority

    pq_element getMax(); // return a pq_element having maximum priority

    bool empty(); // is it empty?

    string printPQ();
};