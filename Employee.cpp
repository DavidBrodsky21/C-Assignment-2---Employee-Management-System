#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

#include "Employee.h"
#include "Log.h"

using namespace std;

Employee::Employee(int idVal, string nameVal, string dateOfBirthVal, string SSNVal, string departmentVal, string positionVal)
{
	ID = idVal;
	name = nameVal;
	dateOfBirth = dateOfBirthVal;
	SSN = SSNVal;
	department = departmentVal;
	position = positionVal;
}

void Employee::empSetter(int idVal, string nameVal, string dateOfBirthVal, string SSNVal, string departmentVal, string positionVal)
{
	ID = idVal;
	name = nameVal;
	dateOfBirth = dateOfBirthVal;
	SSN = SSNVal;
	department = departmentVal;
	position = positionVal;
}

void Employee::printElement()
{
	cout << "ID: " << ID << "  Name: " << name << "  Date of Birth: " << dateOfBirth << "  SSN: "<< SSN 
		<< "  Department: " << department << "  Position: " << position << endl;
}
