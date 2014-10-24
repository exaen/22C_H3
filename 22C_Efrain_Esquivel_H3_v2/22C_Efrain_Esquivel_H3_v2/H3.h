#ifndef SORTS_H
#define SORTS_H

#include <string>
using namespace std;

class Sorts
{
private:
	// Declare a structure for the list
	struct ListNode
	{
		string line;
		ListNode *next;         // To point to the next node
		ListNode *previous;		// To point to the previous node
	};

	ListNode *head;				// List head pointer
	int count;

public:
	// Constructor
	Sorts();

	// Destructor
	~Sorts();

	// Linked list operations
	void insertNode(string line, int index);
	int lineCount();
	void displayListF(int start, int end) const;
	void displayListB(int start, int end, int lines) const;
	string nodeData(int index);
	void deleteLines(int start, int end);

};
#endif
