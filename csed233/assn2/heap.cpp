#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

string PriorityQueue::printPQ()
{
    string answer;
    for (int i = 0; i < size; i++)
        answer += to_string(heap[i].value) + " ";
    return answer;
}

bool PriorityQueue::insert(int priority, int value)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (size >= MAX_SIZE)
        throw "Error";

    heap[size++] = pq_element{priority, value};
    for (size_t i = size; i > 1; i >>= 1)
        if (heap[i - 1].priority > heap[(i >> 1) - 1].priority) {
            pq_element tmp = heap[i - 1];
            heap[i - 1] = heap[(i >> 1) - 1];
            heap[(i >> 1) - 1] = tmp;
        }

    return true;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::removeMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (!size)
        throw "Empty";

    heap[0] = heap[--size];

    for (size_t i = 1; i <= size / 2;) {
        size_t n = i * 2 + (i * 2 < size && heap[i * 2].priority > heap[i * 2 - 1].priority);
        if (heap[i - 1].priority < heap[n - 1].priority) {
            pq_element tmp = heap[i - 1];
            heap[i - 1] = heap[n - 1];
            heap[n - 1] = tmp;
        }
        i = n;
    }

    return true;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

pq_element PriorityQueue::getMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (size)
        return heap[0];
    else
        throw "Empty";

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::empty()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return !size;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
