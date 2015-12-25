/************************************************************************************
Title: Employee Logs (HW2)
Author: David Brodsky
Created on: July 28, 2015
Description:  Simulates an Employee Management system
************************************************************************************/


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

#include "Employee.h"
#include "Log.h"

using namespace std;

//DECLARE FUNCTIONS

void readFiles(vector<Employee> &employeeList, vector<Log> &timeLog);

//HELPER FUNCTIONS
double dailyHoursWorked(vector<Log> timeLog, int i);
double totalHoursWorked(vector<Log> timeLog, int ID);

//MENU FUNCTIONS
void displayOptions();
void searchFunction(vector<Employee> employeeList, vector<Log> timeLog);
void logInLogOutFunction(vector<Log> timeLog);
void editRecords(vector<Employee> &employeeList);
void saveAndExit(vector<Employee> &employeeList);


int main(){
	vector<Employee> employeeList;
	vector<Log> timeLog;
	
	readFiles(employeeList, timeLog);

	int choice; //stores which menu item user chooses
	bool exitProg = false;

	while(exitProg == false)
	{
		cout << "\n\nSelect an option by entering menu choice \n";
		displayOptions();
		cout << endl;
		cin >> choice;
		cout << "\nYou chose option " << choice << endl << endl;
		
		switch (choice)
		{
			case 1:
				searchFunction(employeeList, timeLog);
				break;
			case 2:
				logInLogOutFunction(timeLog);
				break;
			case 3:
				editRecords(employeeList);
				break;
			case 4:
				saveAndExit(employeeList);
				exitProg = true;
				break;
			default:
				cout << "Exit";
				break;
		}
	}

	cout << endl;
	return 0;
}


//DEFINE FUNCTIONS

//ReadFiles
//Read in the details.txt and timelog.txt files and store info as vectors.
//Return appropriate errors where necessary.
void readFiles(vector<Employee> &employeeList, vector<Log> &timeLog)
{
	Employee emp(0, "", "", "","","");
	Log log1(0, "", 0, 0);

	ifstream infile;
	infile.open("details.txt");

	while(infile.good()) {
		int ID;
		string  name, dateOfBirth, SSN, department, position;
		infile >> ID >> name >> dateOfBirth >> SSN >> department >> position;
		emp.empSetter(ID, name, dateOfBirth, SSN, department, position);
		employeeList.push_back(emp);
	}
	infile.close();

	if (employeeList.size() == 0) 
	{
		cout << "\n\nNo entries were read from the \"details.txt\" file.  Please make sure that the file exists and is not blank.\n\n";
		exit(1);
	}

	infile.open("timelog.txt");

	while(infile.good()) {
		int ID, arrivalTime, departureTime;
		string date;

		infile >> ID >> date >> arrivalTime >> departureTime;
		log1.logSetter(ID, date, arrivalTime, departureTime);
		timeLog.push_back(log1);
	}
	infile.close();

	if (timeLog.size() == 0) 
	{
		cout << "\n\nNo entries were read from the \"timelog.txt\" file.  Please make sure that the file exists and is not blank.\n\n";
		exit(1);
	}
}


//HELPER FUNCTIONS - used for implementing the menu options

//Calculate number of hours worked by an individual in a given day
//perform appropriate type conversions for time vars
double dailyHoursWorked(vector<Log> timeLog, int i)
{
	double arrivalTimeDouble, departureTimeDouble, dailyHoursWorked;

	arrivalTimeDouble = timeLog[i].arrivalTime/100.0 + (timeLog[i].arrivalTime % 100)/60.0 ;
	departureTimeDouble = timeLog[i].departureTime/100.0 + (timeLog[i].departureTime % 100)/60.0;
	dailyHoursWorked = departureTimeDouble - arrivalTimeDouble;
	return dailyHoursWorked; 
}

//Calculate the total number of hours an individual with a given ID (idVal) worked through history
double totalHoursWorked(vector<Log> timeLog, int idVal)
{
	double totalHoursWorked = 0.0 , dailyHours = 0.0;
	for (int j = 0; j < timeLog.size(); j++)
	{
		if (timeLog[j].ID == idVal)
		{
			dailyHours = dailyHoursWorked(timeLog, j);
			totalHoursWorked += dailyHours;
		}
	}
	return totalHoursWorked;
}


//MENU FUNCTIONS - implement what each menu item is supposed to do

//Display the menu options
void displayOptions(){
		cout << "1. Search User" << endl
			<< "2. View Time Logs" << endl
			<< "3. Update Information" << endl
			<< "4. Save and Exit" << endl;
}


//Menu item 1 - search for an employee by any combination of ID, Name, Department, or Position
void searchFunction(vector<Employee> employeeList, vector<Log> timeLog)
{
	int idVal;
	string nameVal, departmentVal, positionVal;

	cout << "You may search for an employee using any combination of the following criterion:\nID, name, department, and/or position.\n"
		<< "\nFor each search criterion that you'd like to use, enter its value when prompted.\n"
		<< "\nIf you do not wish to use a given criterion please enter \"-1\".\n";
	cout << "ID: \n";
	cin >> idVal;
	cout << "\nName: \n";
	cin >> nameVal;
	cout << "\nDepartment: \n";
	cin >> departmentVal;
	cout << "\nPosition: \n";
	cin >> positionVal;

	cout << "\nThank you!  The following individuals match your search criteria:\n";

	int employeesFound = 0;
	for (int i = 0; i < employeeList.size(); i++)
	{
		//Check whether a user wishes to use a given criterion AND the criterion matches a given entry
		if (
			(idVal == -1 || employeeList[i].ID == idVal) &&
			(nameVal == "-1" || employeeList[i].name == nameVal) &&
			(departmentVal == "-1" || employeeList[i].department == departmentVal) &&
			(positionVal == "-1" || employeeList[i].position == positionVal)
			)
		{
			employeesFound++;
			employeeList[i].printElement();
			cout << endl << totalHoursWorked(timeLog, employeeList[i].ID) << " total hours worked.\n\n";
		}
	}
	cout << "\nIn total, " << employeesFound << " individual(s) matched your search criteria.\n";
	if (employeesFound == 0)
	{
		cout << "Since no individuals matched your search request, you may want to revise or loosen your search criteria.\n";
	}
}

//Menu item 2 - return an individual's time log history
void logInLogOutFunction(vector<Log> timeLog)
{
	int idVal;
	bool employeeIDFound = false;
	cout << "Enter the ID of the individual whose time log you would like to see: \n";
	cin >> idVal;
	cout << "The individual's time log history is below:\n";
	for (int i = 0; i < timeLog.size(); i++)
	{
		if(timeLog[i].ID == idVal)
		{
			employeeIDFound = true;
			cout << timeLog[i].date << "  "
				<< timeLog[i].arrivalTime << "  " 
				<< timeLog[i].departureTime << "  " 
				<< dailyHoursWorked(timeLog, i) << endl; 
		}
	}

	if (employeeIDFound == false)
	{
		cout << "\n\nERROR:  EMPLOYEE ID NOT FOUND!";
		return;
	}
}

//Menu item 3 - Edit an employee's records
void editRecords(vector<Employee> &employeeList)
{
	cout << "Edit User Details\n_________________\n";

	int idVal; 
	string parameter, newVal, yesOrNo;
	bool continueFlag = true;
	cout << "\nEnterID:  ";
	cin >> idVal;

	while(continueFlag)
	{
		cout << "\nEnter parameter to change:  ";
		cin >> parameter;
		cout << "Enter new value:  ";
		cin >> newVal;

		bool employeeIDFound = false;
		for (int i = 0; i < employeeList.size(); i++)
		{
			if(employeeList[i].ID == idVal)
			{
				employeeIDFound = true;
				if(parameter == "name")
				{
					employeeList[i].name = newVal;
				} 
				else if(parameter =="dateOfBirth")
				{
					employeeList[i].dateOfBirth = newVal;
				}	
				else if(parameter =="SSN")
				{
					employeeList[i].SSN = newVal;
				}
				else if(parameter =="department")
				{
					employeeList[i].department = newVal;
				}
				else if(parameter =="position")
				{
					employeeList[i].position = newVal;
				}
				else
				{
					cout << "Not a valid parameter name.\n";		 
				}
			}
		}

		if (employeeIDFound == false)
		{
			cout << "\n\nERROR:  EMPLOYEE ID NOT FOUND!";
			return;
		}

		cout << "\n\nValue updated. Change another parameter (Y/N)?  ";
		cin >> yesOrNo;
		if(yesOrNo == "N")
		{
			continueFlag = false;
		}
	}

}

//Menu item 4 - Save to the details.txt file and exit the program
void saveAndExit(vector<Employee> &employeeList)
{
	ofstream myfile;
	myfile.open ("details.txt");
	
	for (int i = 0; i < employeeList.size(); i++)
	{
		myfile << employeeList[i].ID << " " 
				<< employeeList[i].name << " "
				<< employeeList[i].dateOfBirth << " "
				<< employeeList[i].SSN << " "
				<< employeeList[i].department << " "
				<< employeeList[i].position
				<< endl;
	}

	myfile.close();
}


