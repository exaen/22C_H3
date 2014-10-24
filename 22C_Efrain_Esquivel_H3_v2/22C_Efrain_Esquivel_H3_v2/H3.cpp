// Implementation file for the Sorts class
#include <iostream>
#include "H3.h"

using namespace std;

/** Constructor */
Sorts::Sorts() {
	count = NULL;
	head = new ListNode;		// Head sentinel node
	head->previous = head;		// Circularly-Linked
	head->next = head;			// Doubly-Linked

}
/** Member function displayListF iterates through the
	list of nodes from one line position to another
	in order and displays the contents in them. */
void Sorts::displayListF(int start, int end) const {
	ListNode *walker;
	walker = head->next;

	for (int c = 1; c < start; c++)
		walker = walker->next;

	for (int c = start; c <= end; c++){
		cout << c << ": " << walker->line << endl;
		walker = walker->next;
	}

	cout << endl << endl;
}
/** Member function displayListB iterates through the
	list of nodes from one line position to another
	in reverse order and displays the contents in them. */
void Sorts::displayListB(int start, int end, int lines) const
{
	ListNode *walker;
	walker = head->previous;

	for (int c = lines; c > start; c--)
		walker = walker->previous;

	for (int c = start; c >= end; c--){
		cout << c << ": " << walker->line << endl;
		walker = walker->previous;
	}

	cout << endl << endl;
}
/** Member function nodeData iterates through the
	list of nodes from head to head and returns
	the data found in the node specified by an
	index location. */
string Sorts::nodeData(int index){
	ListNode *walker;
	walker = head->next;

	for (int c = 0; c < index; c++)
		walker = walker->next;

	return walker->line;
}
/** Member function deleteLines iterates through the
	list of nodes from one line position to another
	deleting the nodes in the process. */
void Sorts::deleteLines(int start, int end)
{
	ListNode *walker;
	walker = head->next;

	for (int c = 1; c < start; c++)
		walker = walker->next;

	for (int c = start; c <= end; c++){
		ListNode *deleteNode = walker;
		walker = walker->next;
		walker->previous->previous->next = walker;
		walker->previous = walker->previous->previous;
		delete deleteNode;
	}
	
	cout << "Nodes " << start << " through " << end << " deleted." << endl;
}
/** Member function lineCount iterates through the
	list of nodes from head to head. For each node
	it passes, it adds 1 to int count. It returns
	the number of nodes in the list. */
int Sorts::lineCount()
{
	ListNode *walker;
	walker = head->next;

	int count = NULL;

	while (walker != head)
	{
		count++;
		walker = walker->next;
	}

	return count;
}
/** Member function insertNode iterates through the
	list of nodes until it reaches a specified index
	location. It then inserts a new node in that
	position. */
void Sorts::insertNode(string line, int index)
{
	ListNode *newNode;
	ListNode *walker;

	newNode = new ListNode;
	newNode->line = line;

	walker = head->next;

	for (int c = 0; c < index; c++)
		walker = walker->next;

	newNode->next = walker->previous->next;
	newNode->previous = walker->previous;
	walker->previous->next = newNode;
	walker->previous = newNode;

	count++;
}

/** Destructor: This iterates through the list
	of nodes and deletes them in the process. */
Sorts::~Sorts()
{
	ListNode *walker;
	ListNode *nextNode;

	walker = head->next;
	while (walker != head){
		nextNode = walker->next;
		delete walker;
		walker = nextNode;
	}
}
