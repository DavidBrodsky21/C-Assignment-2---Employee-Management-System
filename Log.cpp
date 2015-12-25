#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

#include "Employee.h"
#include "Log.h"

using namespace std;

Log::Log(int idVal, string dateVal, int arrivalTimeVal, int departureTimeVal)
{
	ID = idVal;
	date = dateVal;
	arrivalTime = arrivalTimeVal;
	departureTime = departureTimeVal;
}

void Log::logSetter(int idVal, string dateVal, int arrivalTimeVal, int departureTimeVal)
{
	ID = idVal;
	date = dateVal;
	arrivalTime = arrivalTimeVal;
	departureTime = departureTimeVal;
}