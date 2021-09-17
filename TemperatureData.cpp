/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#include "TemperatureData.h"
using namespace std;

TemperatureData::TemperatureData() {} //initialize everything

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature): id(id), year(year), month(month), temperature(temperature) {} //initialize everything

TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) {
	// Implement this


	// location
	if (this->id < b.id) {
		return true;
	} else if (this->id == b.id) {
		// continue
	} else {
		return false;
	}

	// date (year then month)
	if (this->year < b.year) {
		return true;
	} else if (this->year == b.year) {
		// continue
	} else {
		return false;
	}

	if (this->month < b.month) {
		return true;
	} else if (this->month == b.month){
		// continue
	} else {
		return false;
	}

	return false;

}

