#include <iostream>
#include <string>
#include "priority_queue.h"
using namespace std;

int main(int argc, char* argv[])
{
    PriorityQueue<string> queue;

    queue.insert("d");
    queue.insert("b");
    queue.insert("a");
    queue.insert("c");
    queue.insert("e");

    cout << "Empty? " << queue.isEmpty() << endl;
    cout << "pop: " << queue.pop() << endl;
    cout << "top: " << queue.top() << endl;

    return 0;
}
