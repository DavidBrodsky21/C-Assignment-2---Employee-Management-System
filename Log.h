#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Log {
public:
	Log(int idVal, string dateVal, int arrivalTimeVal, int departureTimeVal);
	void logSetter(int idVal, string dateVal, int arrivalTimeVal, int departureTimeVal);

	int ID;
	string date;
	int arrivalTime;
	int departureTime;
};

#endif