/** Homework 2 - 100 Points - CIRCULARLY-DOUBLY-LINKED LISTS with One Sentinel Node

Project : Write a program to process a text using a doubly-linked list
with sentinel nodes.Read lines of text form input.txt and insert them
into a doubly-linked list. Your program should be able to process the
following commands :

T									Display the total number of lines in the text.
F									Print all lines from first to last (show the line numbers: 1, 2, 3, etc.)
B									Print all lines from last to first (show the line numbers)
I <line number> <text>				// I 3 This is the new line of text to be inserted // Insert a new line of text at position 3 in the list
L <line number 1> <line number 2>	// L 2 5 // List lines 2 to 5 inclusive (show the line numbers) // L 5 2 // List lines 5 to 2 inclusive, in reverse order (show the line numbers)
D <line number 1> <line number 2>	// D 3 7   // D 7 3   // Delete lines 3 to 7 inclusive
S <output file name>				// S out.txt // Save the updated text to an output file
H									Help: Display instructions for T, F, B, I, L, D, S, H, A and Q
A									About: Display information about the developer: // Your name, class, quarter, year, college
Q									Quit editing the file (don’t forget to save it!)

Test your program by choosing each command at least once.
Insert a new sorting algorithm in the list, “Shaker Sort” after “Selection Sort”.
Delete “Bubble Sort”.Delete a range, for instance “Odd - even Sort” to “Sample Sort”, etc.
The input file contains some blank lines at the end.
You could test your program by removing those lines too. 

Efrain Esquivel
CIS 22C
De Anza College
Fall 2014

Compiler/IDE: Visual Studio 2013
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "H3.h"
//#include "MemTracker.h" // To check for memory leaks.

using namespace std;

const string FILE_NAME = "input.txt";
const int INVALID_CHARS = 9;
const int FIRST_ELEMENT = 1;

void commandExecution	(Sorts *);
char getValidCommand	(string &, string &, string &);
bool getValidPosition	(Sorts *, int &);
bool checkInteger		(string);
bool readFile			(Sorts *);
void saveToFile			(Sorts *, string);
void insertNewLine		(Sorts *, int, string);
void listLines			(Sorts *, int, int);
void deleteLines		(Sorts *, int, int);
void help();
void about();

int main(){
	Sorts *list = new Sorts;
	char option;

	if (!readFile(list))
		return 1;

	commandExecution(list);

	delete list;

	return 0;
}
/** Function commandExecution prompts the user to enter a command.
	If the user enters an invalid command, an error message
	is displayed and the prompt is executed again. The commands call
	various functions:
		* T - returns the amount of lines in the list.
		* F - prints all the lines in the list in order.
		* B - prints all the lines in the list in reverse order
		* I - inserts a new line at a certain position
		* L - lists lines between two locations
				the order depends if the first integer is larger or smaller
				than the other
		* D - deletes lines between two locations
		* S - saves the current list to a file
		* A - about the author
		* Q - quits the program */
void commandExecution(Sorts *list){
	char option;
	string str1 = "";  // Usually an integer or string
	string str2 = "";  // Usually an integer
	string str3 = "";  // Always a string

	while (cout << "Enter command> ", option = getValidCommand(str1, str2, str3), option != 'Q' && option != 'q'){
		option = toupper(option);
		switch (option){
		case 'T':
			cout << "Items in list: " << list->lineCount() << endl;
			break;
		case 'F':
			list->displayListF(FIRST_ELEMENT, list->lineCount());
			break;
		case 'B':
			list->displayListB(list->lineCount(), FIRST_ELEMENT, list->lineCount());
			break;
		case 'I':
			if (checkInteger(str1))
				insertNewLine(list, stoi(str1), str2 + " " + str3);
			break;
		case 'L':
			if (checkInteger(str1) && checkInteger(str2))
				listLines(list, stoi(str1), stoi(str2));
			break;
		case 'D':
			if (checkInteger(str1) && checkInteger(str2))
				deleteLines(list, stoi(str1), stoi(str2));
			break;
		case 'S':
			saveToFile(list, str1);
			break;
		case 'H':
			help();
			break;
		case 'A':
			about();
			break;
		default:
			cout << "Invalid command. Enter H for a list of commands." << endl;
		}
	}
}
/** Function getValidCommand is an extensive input validation function.
	Delia, if you read these comments, I'm pretty proud of this one. :) */
char getValidCommand(string &str1, string &str2, string &str3) {
	string buffer = "";
	string input[4] = { "", "", "", "" };
	int start = NULL;  // Starting at the command letter position
	int index = NULL;  // Stores the position of a space character in a line of text.
	
	getline(cin, buffer);
	if (buffer == "")
		return 'x';								// Sentinel char to display error message.
	// Will keep running until no more spaces are found and only if more than one word was written.
	for (int i = 0; index != string::npos && buffer.length() != 1; i++) {
		index = buffer.find(' ', start);
		if (i < 3)	{ // Stop adding words to the array if more than 3 words exist.
			input[i] = buffer.substr(start, index - start);
			start = index + 1;
		}
		else {
			input[3] += buffer.substr(start, buffer.length() - (start - 1));
			break;
		}
	}

	if (input[0].length() > 1) {   // If the length of the first item entered is more than 1, it is an invalid command.
		cin.clear();							// Likewise, if the amount of words entered are more than 3, that is also invalid.
		return 'x';								// Sentinel char to display error message.
	}
	str1 = input[1];
	str2 = input[2];
	str3 = input[3];							// This third variable is only used for inserting a new line.
	// The front of the buffer has been verified to be only 1 character, so the front is returned.
	return buffer.front();
}
/** Function getValidPosition gets a valid integer within the list's possible positions. */
bool getValidPosition(Sorts *list, int &pos){
	if (pos > list->lineCount() || pos < 1){
		cout << "Line position is greater than the amount of\n"
			<< "items in the list, or is less than 1.\n\n";
		return false;
	}
	
	return true;
}
/** Function checkInteger checks if a line position/index is actually
	an integer entered by the user. */
bool checkInteger(string in) {
	int out;
	stringstream ss(in);
	if (ss >> out && !(ss >> in))
		return true;
	cin.clear();
	cerr << "Invalid integer detected.\n";
	return false;
}
/** Function readFile reads a file and stores each line in a circularly-doubly-linked list. */
bool readFile(Sorts *list){
	ifstream inFile;
	string buffer;
	bool empty = true;
	int index = 0;

	inFile.open(FILE_NAME);
	if (!inFile){
		cout << "Error opening " << FILE_NAME << "!\n";
		return false;
	}

	while (inFile.good()){
		getline(inFile, buffer);
		list->insertNode(buffer, index);
		empty = false;
		index++;
	}

	inFile.close();

	if (empty)
		return false;

	return true;
}
/** Function saveToFile saves the current list into a file. */
void saveToFile(Sorts *list, string fileName){
	int found = NULL;
	char invalid[INVALID_CHARS] = { '\'', '/', ':', '*', '?', '"', '<', '>', '|' };
	ofstream outFile;

	if (fileName == "") {
		cout << "File name may not be blank." << endl;
		return;
	}

	for (int i = 0; i < INVALID_CHARS; i++) {
		found = fileName.find(invalid[i]);
		if (found != string::npos) {
			cout << "File name may not contain these characters: \ / : * ? \" < > |" << endl;
			return;
		}
	}

	outFile.open(fileName);

	for (int index = 0; index != list->lineCount(); index++)
		outFile << list->nodeData(index) << endl;

	outFile.close();
}
/** Function insertNewLine inserts a string into a specified position
	in the list. */
void insertNewLine(Sorts *list, int index, string line){
	if (getValidPosition(list, index)) {
		list->insertNode(line, index - 1);
		cout << "\"" << line << "\" inserted at line position " << index << ".\n";
	}
}
/** Function listLines lists lines between two specified list positions. */
void listLines(Sorts *list, int start, int end){	
	if (getValidPosition(list, start) && getValidPosition(list, end)){
		if (start > end)  // First integer is larger
			list->displayListB(start, end, list->lineCount());
		else              // First integer is smaller
			list->displayListF(start, end);
	}
}
/** Function deleteLines deletes lines between two locations. */
void deleteLines(Sorts *list, int start, int end) {
	if (getValidPosition(list, start) && getValidPosition(list, end)){
		if (start > end)
			list->deleteLines(end, start);
		else
			list->deleteLines(start, end);
	}
}
/** Function help displays all the commands and a brief description of each. */
void help(){
	cout << "Commands (not case sensitive)\n\n"
		 << "\tT\n\tDisplay the total number of lines in the list.\n\n"
		 << "\tF\n\tPrint all lines from first to last.\n\n"
		 << "\tB\n\tPrint all lines from last to first.\n\n"
		 << "\tI <line number> <text>\n\tInsert a new line of text at desired position.\n\n"
		 << "\tL <line number 1> <line number 2>\n\tList lines between two line numbers inclusively.\n"
		 << "\tIf the first number is less than the second,\n\tthe lines will be displayed in order;\n"
		 << "\totherwise, the lines will be displayed in reverse order.\n\n"
		 << "\tD <line number 1> <line number 2>\n\tDelete lines between two line numbers inclusively.\n\n"
		 << "\tS <output file name>\n\tSave the updated text to a specified file.\n\n"
		 << "\tH\n\tDisplay this guide again.\n\n"
		 << "\tA\n\tAbout the developer.\n\n"
		 << "\tQ\n\tExit the program.\n\n";
}
/** Function about displays information about the developer. */
void about(){
	cout << "\n\tEfrain Esquivel"
		 << "\n\tCIS 22C"
		 << "\n\tFall 2014"
		 << "\n\tDe Anza College\n\n";
}

/** Output - Normal Input

Enter command> t
Items in list: 36
Enter command> f
1: Popular Sorting Algorithms
2:
3: Insertion Sort
4: Selection Sort
5: Bubble Sort
6:
7: Shell Sort
8: Comb Sort
9: Merge Sort
10: Heap Sort
11: Quick Sort
12:
13: Counting Sort
14: Bucket Sort
15: Radix Sort
16:
17: Odd-even Sort
18: Flash Sort
19: Burst Sort
20: Postman Sort
21: Stooge Sort
22: Sample Sort
23:
24: While there is a large number of sorting algorithms,
25: in practical implementations a few algorithms predominate.
26:
27: Insertion sort is widely used for small data sets,
28: while for large data sets an efficient sorting algorithm
29: is used, such as heap sort, merge sort, or quicksort.
30:
31:
32:
33:
34:
35:
36:


Enter command> b
36:
35:
34:
33:
32:
31:
30:
29: is used, such as heap sort, merge sort, or quicksort.
28: while for large data sets an efficient sorting algorithm
27: Insertion sort is widely used for small data sets,
26:
25: in practical implementations a few algorithms predominate.
24: While there is a large number of sorting algorithms,
23:
22: Sample Sort
21: Stooge Sort
20: Postman Sort
19: Burst Sort
18: Flash Sort
17: Odd-even Sort
16:
15: Radix Sort
14: Bucket Sort
13: Counting Sort
12:
11: Quick Sort
10: Heap Sort
9: Merge Sort
8: Comb Sort
7: Shell Sort
6:
5: Bubble Sort
4: Selection Sort
3: Insertion Sort
2:
1: Popular Sorting Algorithms


Enter command> i 5 Selection Sort
"Selection Sort" inserted at line position 5.
Enter command> f
1: Popular Sorting Algorithms
2:
3: Insertion Sort
4: Selection Sort
5: Selection Sort
6: Bubble Sort
7:
8: Shell Sort
9: Comb Sort
10: Merge Sort
11: Heap Sort
12: Quick Sort
13:
14: Counting Sort
15: Bucket Sort
16: Radix Sort
17:
18: Odd-even Sort
19: Flash Sort
20: Burst Sort
21: Postman Sort
22: Stooge Sort
23: Sample Sort
24:
25: While there is a large number of sorting algorithms,
26: in practical implementations a few algorithms predominate.
27:
28: Insertion sort is widely used for small data sets,
29: while for large data sets an efficient sorting algorithm
30: is used, such as heap sort, merge sort, or quicksort.
31:
32:
33:
34:
35:
36:
37:


Enter command> d 6 6
Nodes 6 through 6 deleted.
Enter command> f
1: Popular Sorting Algorithms
2:
3: Insertion Sort
4: Selection Sort
5: Selection Sort
6:
7: Shell Sort
8: Comb Sort
9: Merge Sort
10: Heap Sort
11: Quick Sort
12:
13: Counting Sort
14: Bucket Sort
15: Radix Sort
16:
17: Odd-even Sort
18: Flash Sort
19: Burst Sort
20: Postman Sort
21: Stooge Sort
22: Sample Sort
23:
24: While there is a large number of sorting algorithms,
25: in practical implementations a few algorithms predominate.
26:
27: Insertion sort is widely used for small data sets,
28: while for large data sets an efficient sorting algorithm
29: is used, such as heap sort, merge sort, or quicksort.
30:
31:
32:
33:
34:
35:
36:


Enter command> d 17 22
Nodes 17 through 22 deleted.
Enter command> f
1: Popular Sorting Algorithms
2:
3: Insertion Sort
4: Selection Sort
5: Selection Sort
6:
7: Shell Sort
8: Comb Sort
9: Merge Sort
10: Heap Sort
11: Quick Sort
12:
13: Counting Sort
14: Bucket Sort
15: Radix Sort
16:
17:
18: While there is a large number of sorting algorithms,
19: in practical implementations a few algorithms predominate.
20:
21: Insertion sort is widely used for small data sets,
22: while for large data sets an efficient sorting algorithm
23: is used, such as heap sort, merge sort, or quicksort.
24:
25:
26:
27:
28:
29:
30:


Enter command> d 24 30
Nodes 24 through 30 deleted.
Enter command> f
1: Popular Sorting Algorithms
2:
3: Insertion Sort
4: Selection Sort
5: Selection Sort
6:
7: Shell Sort
8: Comb Sort
9: Merge Sort
10: Heap Sort
11: Quick Sort
12:
13: Counting Sort
14: Bucket Sort
15: Radix Sort
16:
17:
18: While there is a large number of sorting algorithms,
19: in practical implementations a few algorithms predominate.
20:
21: Insertion sort is widely used for small data sets,
22: while for large data sets an efficient sorting algorithm
23: is used, such as heap sort, merge sort, or quicksort.

Enter command> s out.txt
Enter command> a

Efrain Esquivel
CIS 22C
Fall 2014
De Anza College

Enter command> h
Commands (not case sensitive)

T
Display the total number of lines in the list.

F
Print all lines from first to last.

B
Print all lines from last to first.

I <line number> <text>
Insert a new line of text at desired position.

L <line number 1> <line number 2>
List lines between two line numbers inclusively.
If the first number is less than the second,
the lines will be displayed in order;
otherwise, the lines will be displayed in reverse order.

D <line number 1> <line number 2>
Delete lines between two line numbers inclusively.

S <output file name>
Save the updated text to a specified file.

H
Display this guide again.

A
About the developer.

Q
Exit the program.

Enter command>

Enter command> q
Press any key to continue . . .

*/

/** Output - Input Validation Test

Enter command> ihefoiwf
Invalid command. Enter H for a list of commands.
Enter command> fg
Invalid command. Enter H for a list of commands.
Enter command> i 3 b
"b " inserted at line position 3.
Enter command> i b 3
Invalid integer detected.
Enter command> l 400 -3
Line position is greater than the amount of
items in the list, or is less than 1.

Enter command> d y 3
Invalid integer detected.
Enter command> s out*.txt
File name may not contain these characters : / : *? " < > |
Enter command> s out.txt
Enter command> qq
Invalid command.Enter H for a list of commands.
Enter command>
Invalid command.Enter H for a list of commands.
Enter command>
Invalid command.Enter H for a list of commands.
Enter command> q
Press any key to continue . . .

*/