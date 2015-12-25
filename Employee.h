#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Employee {
public:
	Employee(int idVal, string nameVal, string dateOfBirthVal, string SSNVal, string departmentVal, string positionVal);
	void empSetter(int idVal, string nameVal, string dateOfBirthVal, string SSNVal, string departmentVal, string positionVal);
	void printElement();

	int ID;
	string name;
	string dateOfBirth;
	string SSN;
	string department;
	string position;
};

#endif