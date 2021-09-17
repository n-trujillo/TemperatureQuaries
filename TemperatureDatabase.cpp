#include "TemperatureDatabase.h"

#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {

	// get a line of data 
	ifstream ifs;
	std::string line = "";

	std::string location;
	int year;
	int month;
	double temp;

	ifs.open(filename);

	if(!ifs.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
	}

	while (getline(ifs, line)) { // while there is an entry on the next line

		// put the line into the string streams
		istringstream ss(line);

		// evaluate
		ss >> location >> year >> month >> temp;
		if (temp == -99.99) {
			cout << "Error: Other invalid input" << endl;
			ss.clear();
			continue;
		}

		if (year < 1800 || year > 2021) {
			cout << "Error: Invalid year " << year << endl;
			ss.clear();
			continue;
		}

		if (month < 1 || month > 12) {
			cout << "Error: Invalid month " << month << endl;
			ss.clear();
			continue;
		}

		if (temp < -50 || temp > 50) {
			cout << "Error: Invalid temperature " << temp << endl;
			ss.clear();
			continue;
		}

		// insert information into the linked list
		records.insert(location, year, month, temp);

	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	ifstream ifs;
	ifs.open(filename);

	string location;
	string function;
	int lowerYear;
	int upperYear;
	int sum;
	int count;
	double avg;
	double mode;

	ifs >> location;
	ifs >> function;
	ifs >> lowerYear;
	ifs >> upperYear;

	if (function == "AVG") {
		// iterate though all nodes with year values lower -> uper

		Node* tempHead = records.getHead();
		Node* currentNode = nullptr;

		while (tempHead != nullptr) {
			// define currentNode to be head
			currentNode = tempHead;

			// update head to be the next node
			tempHead = tempHead->next;

			// check if valid year and location 
			if ((currentNode->data.year >= lowerYear) && (currentNode->data.year <= upperYear) && (currentNode->data.id == location)) {
				// add the temp value to the sum
				sum += currentNode->data.temperature;
				count ++;
			}

		}

		// count and sum has been found
		// calculate avg
		avg = sum / count;

		// output quary
		ofstream dataout("result.dat");

		if (!dataout.is_open()) {
			cout << "Error: Unable to open " << filename << endl;
			exit(1);
		}

		dataout << location << " " << lowerYear << " " << upperYear << " " << function << " " << avg << endl;

	}

	if (function == "MODE") {
		// iterate though all nodes with year values lower -> uper

		Node* tempHead = records.getHead();
		Node* currentNode = nullptr;

		while (tempHead != nullptr) {
			// define currentNode to be head
			currentNode = tempHead;

			// update head to be the next node
			tempHead = tempHead->next;

			// check if valid year and location 
			if ((currentNode->data.year >= lowerYear) && (currentNode->data.year <= upperYear) && (currentNode->data.id == location)) {
				// convert the temperature value to nearest integer

				double actualTemp = currentNode->data.temperature;
				int lowerTemp = currentNode->data.temperature;

				if ((actualTemp - lowerTemp) <= 0.5) {
					mode = lowerTemp;
				}

				if ((actualTemp - lowerTemp) > 0.5) {
					mode = lowerTemp + 1;
				}

			}

		}
	}


}
