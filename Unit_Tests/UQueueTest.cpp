/*
Lab03A
Names : Joseph Saunders and Joshua Gomes
Class : CIS22C61Y
*/
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Queue.h"
using namespace std;

//******************************************************************************
// int main() - Main declares defines 3 arrays of 10 elements each. 
// An int, string and dollar.
//
// Our list template allows us to sort whatever type is passed in ascending
// and descending order or unsorted. For our case to demonstrate the template
// support for list in descending order we print integers, to demonstrate 
// support for ascending order we print strings and to demonstrate unordered
// insertion we print rupee objects.
// 
// PSEUDOCODE:
// 
//	1.  Print Header
//	2.  Demonstrate Stack implementation of Linked List
//	3.	Demonstrate Queue implementation of Linked List
//******************************************************************************
int main()
{
	// 1.  Print Header
	cout	<< "Unit Test for the Queue portion.\n"
			<< endl;

	// 3. Instantiate and demonstrate Queue
	Queue<int> myQueue;
	myQueue.enqueue(23); 
	myQueue.enqueue(454);
	myQueue.enqueue(567);
	myQueue.enqueue(5654);
	myQueue.enqueue(222);


	// Printing the Queue
	cout << "All items queued as follows: \n";
	myQueue.print();

	myQueue.dequeue();
	myQueue.dequeue();
	cout << endl << "All items after 2 dequeued as follows: \n";
	myQueue.print();

	cout << myQueue.front() << endl;
	//cout << "Printing rear of queue: \n";
	//cout << myQueue.rear() << endl;

	myQueue.dequeue();
	myQueue.dequeue();
	myQueue.dequeue();
	cout << endl << "All items dequeued as follows: \n";
	myQueue.print();
	if (myQueue.isEmpty())
		cout << "List is EMPTY.\n";
	else
		cout << "List still has shit in it.\n";

	return 0;
}
