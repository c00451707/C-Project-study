#include <iostream>
#include <string>
#include "queuetp.h"

int main()
{
    using std::string;
    using std::cin;
    using std::cout;
    using std::endl;

    QueueTp<string> cs(5);
    string temp;

    while(!cs.isfull())
    {
        cout << "Please enter your name. You will be served in the order of arrival.\n";
        cout << "name: ";
        getline(cin, temp);
        cs.enqueue(temp);
    }

    cout << "The queue is full. Processing begins!\n";

    while (!cs.isempty())
    {
        cs.dequeue(temp);
        cout << "Now Processing " << temp << "...\n";
    }
    return 0;
}

/*
    Please enter your name. You will be served in the order of arrival.
    name: Kinesey Millhone
    Please enter your name. You will be served in the order of arrival.
    name: Adam Dalgliesh
    Please enter your name. You will be served in the order of arrival.
    name: Andrew Dalziel
    Please enter your name. You will be served in the order of arrival.
    name: Kay Scarpetta
    Please enter your name. You will be served in the order of arrival.
    name: Richard Jury
    The queue is full. Processing begins!
    Now Processing Kinesey Millhone...
    Now Processing Adam Dalgliesh...
    Now Processing Andrew Dalziel...
    Now Processing Kay Scarpetta...
    Now Processing Richard Jury...
*/