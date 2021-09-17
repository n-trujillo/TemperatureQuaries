#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList(): head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList() {
	clear();
}

// copy constrcutor
// used to create a new linked list based off an already existing one
LinkedList::LinkedList(const LinkedList& source): head(nullptr), tail(nullptr) {


	// create a copy off all the nodes 
	Node* currentNode = nullptr;
	Node* tempHead = source.head;
	Node* prev = nullptr;
	int i = 0;

	while(tempHead != nullptr) {
		// define currentNode to be head
		currentNode = tempHead;

		// update head to be the next node
		tempHead = tempHead->next;

		// make a copy of currentNode on the heap
		Node* newNode = new Node(currentNode->data.id, currentNode->data.year, currentNode->data.month, currentNode->data.temperature);

		// if first instance make it head
		if (i == 0) {
			this->head = newNode;
		}

		if (prev != nullptr) {
			// set prev to point to newNode
			prev->next = newNode;
		}

		// update prev
		prev = newNode;

		i++;
	}

	// update tail
	this->tail = prev;
}

// copy assignment contructor
// sets an already existing linked list equal to another
LinkedList& LinkedList::operator=(const LinkedList& source) {
	// first wipe all existances of the the previously used nodes
	this->clear();

	// create a copy of given linked list and set it equal
		// create a copy off all the nodes 
	Node* currentNode = nullptr;
	Node* tempHead = source.head;
	Node* prev = nullptr;
	int i = 0;

	while(tempHead != nullptr) {
		// define currentNode to be head
		currentNode = tempHead;

		// update head to be the next node
		tempHead = tempHead->next;

		// make a copy of currentNode on the heap
		Node* newNode = new Node(currentNode->data.id, currentNode->data.year, currentNode->data.month, currentNode->data.temperature);

		// if first instance make it head
		if (i == 0) {
			this->head = newNode;
		}

		if (prev != nullptr) {
			// set prev to point to newNode
			prev->next = newNode;
		}

		// update prev
		prev = newNode;

		i++;
	}

	// update tail
	this->tail = prev;

	prev = nullptr;
	tempHead = nullptr;
	currentNode = nullptr;

	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {

	// initialize
	int approach = 9;
	Node* current = head;
	Node* prev = nullptr;

	// create the node
	Node* newNode = new Node(location, year, month, temperature);

	// if empty list
	if (head == nullptr || tail == nullptr) {
		// take approach 0
		approach = 0;

	} else {
		// not empty?

		// check for insert // neither
		if ((*newNode < *tail) && !(*newNode < *head)) {
			approach = 3;
		}

		// check for append // newNode greater than tail
		if (!(*newNode < *tail)) {
			approach = 2;
		}

		// check for prepend // newNode less than head
		if (*newNode < *head) {
			approach = 1;
		}

	}

	// switch for each appraoch

	switch(approach) {

		case 0: // empty list
			head = newNode;
			tail = newNode;
			break;

		case 1: // add to beginning
			// set newNode to point to OGhead
			newNode->next = head;

			// update tail to point to nullptr
			tail->next = nullptr;

			// update head
			head = newNode;

			break;

		case 2: // add to end
			// set tail to point to newNode
			tail->next = newNode;

			// update tail 
			tail = newNode;
			break;

		case 3: // insert

			// find the location of the insert
			while (current != nullptr) {
				prev = current;
				current = current->next;
				// is newNode less than prev?
				if (newNode < prev) {
					break;
				}
				// is newNode less than marker and greater than prev (!< can be seen as greater than or equal to)
				if (*newNode < *current && !(*newNode < *prev)) {
					// yes?
					// break the loop
					break;
				}

				// no?
				// keep looping
			}

			// set prev to point to newNode
		    prev->next = newNode;

		    // set newNode to point to current
		    newNode->next = current;

			break;

		default: 
			cout << "case not accounted for" << endl;
	}

	// insert complete
	// cout << *this << "end of updated list" << endl;

}

void LinkedList::clear() {
	// marker
    Node* currentNode = nullptr;

    // traverse through linekd list
    while(head != nullptr) {
        // define the currentNode to be the head
        currentNode = head;

        // update the head to be the next node
        head = head->next;

        // set the current node to point to nothing
        currentNode->next = nullptr;

        // delete the current node
        delete currentNode;
    }

    // update attributes to all be empty
    head = nullptr;
    tail = nullptr;
    currentNode = nullptr;
}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	// string tools
	string outputString;
	ostringstream infoOSS;

	// ptrs
	Node* currentNode = nullptr;
	Node* tempHead = head;

	// iterate though the linked list
	while (tempHead != nullptr) {

		// define currentNode to be head
		currentNode = tempHead;

		// update head to be the next node
		tempHead = tempHead->next;

		// dump current node info into the output string stream
		infoOSS << currentNode->data.id << " " << currentNode->data.year << " " << currentNode->data.month << " " << currentNode->data.temperature << endl;
	}

	// extract string stream to a single stream
	outputString = infoOSS.str();
	
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
