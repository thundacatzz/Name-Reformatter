#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctype.h>
using namespace std;
// This program was created to take input from a sloppily formatted list of names, then output them in cleaner formatting with a gender and marital correct prefix
// as well as display the original input alongside it.
// Created by Logan Skura 9/20/2022

// These are the i/o stream variables and all of the functions defined outside the main.
ifstream nameData;
ofstream outputFile;
void OpenInputFile();
void OpenOutputFile();
string PrintFirstName(string);
string PrintLastName(string);

// This is an enum defined for deciding the correct prefixes and a related function.
enum MaritalStatus : char { M, S, D };
MaritalStatus m = M;
MaritalStatus ReadStatus(char currentChar, char prevChar);

int main()
{
	OpenInputFile();
	OpenOutputFile();
	
	// These lines format the output and have the heading lines.
	cout << setw(30) << left << "Original Name" << setw(5) << "Standardized Name" << endl << endl;
	outputFile << setw(30) << left << "Original Name" << setw(5) << "Standardized Name" << endl << endl;

	while (!nameData.eof())
	{
		// These are the variables used throughout the main and subfunctions.
		string line;
		string middleInitial = "";
		string firstName = "";
		string lastName = "";
		char currentChar = ' ';
		char prevChar = ' ';
		
		//this block pulls each line from the input, then removes the first two characters that indicate marital status by taking a substring of the line.
		getline(nameData, line);
		int length = (line.length() - 1);
		string modifiedLine = line.substr(2);
		
		for (int i = 0; i <= length; i++)
		{
			prevChar = currentChar;
			currentChar = line[i];
			// This block assumes the formatting of the marital status indicators as the first two characters in the string, then outputs the original line without those characters.
			// It also contains functions calls for the prefixes and the first names.
			if (i == 1)
			{
				cout << setw(30) << modifiedLine;
				outputFile << setw(30) << modifiedLine;
				ReadStatus(currentChar, prevChar);
				cout << PrintFirstName(modifiedLine);
				outputFile << PrintFirstName(modifiedLine);
			}
			
			// This block tests for the period included in the middle initial, then outputs the middle initial, if one exists.
			if (currentChar == '.')
			{
				middleInitial += prevChar;
				cout << " " << middleInitial << '.';
				outputFile << " " << middleInitial << '.';
			}
		}
		cout << " " << PrintLastName(modifiedLine);
		outputFile << " " << PrintLastName(modifiedLine);
		cout << endl;
		outputFile << endl;
	}
	return 0;
}
// This function finds the individual's first name with the location of the comma in the input, then takes it as a substring, deletes the extra whitespace, takes another substring
// without the middle initial, then returns the first name.
string PrintFirstName(string modifiedLine)
{
	string delimiter1 = ",";
	string delimiter2 = ".";
	string firstName = modifiedLine.substr((modifiedLine.find(delimiter1) + 1));
	for (int w = 0; w < 4; w++)
	{
		for (int i = 0; i < firstName.length(); i++)
		{
			if (isspace(firstName[i]))
			{
				firstName.erase(i, 1);
			}
		}
	}
	string trueFirstName = firstName.substr(0, firstName.find(delimiter2) - 1);
	return trueFirstName;
}

// This function finds the individual's last name with the location of the comma in the input, then takes it as a substring and deletes the extra whitespace, then returns the name.
string PrintLastName(string modifiedLine)
{
	string delimiter = ",";
	string lastName = modifiedLine.substr(0, (modifiedLine.find(delimiter)));
	for (int w = 0; w < 4; w++)
	{
		for (int i = 0; i < lastName.length(); i++)
		{
			if (isspace(lastName[i]))
			{
				lastName.erase(i, 1);
			}
		}
	}
	return lastName;
}

// This function reads the characters included in the file that define the name's gender and the individuals marital status, then outputs the correct prefix for them.
MaritalStatus ReadStatus(char currentChar, char prevChar)
{
	char gender = prevChar;
	if (currentChar == 'M')
	{
		m = M;
	}
	if (currentChar == 'S')
	{
		m = S;
	}
	if (currentChar == 'D')
	{
		m = D;
	}
	if (gender == 'M')
	{
		switch (m)
		{
		case M:
			cout << "Mr. ";
			outputFile << "Mr. ";
			break;
		case S:
			cout << "Mr. ";
			outputFile << "Mr. ";
			break;
		case D:
			cout << "Mr. ";
			outputFile << "Mr. ";
			break;
		default:
			break;
		}
	}
	if (gender == 'F')
	{
		switch (m)
		{
		case M:
			cout << "Mrs. ";
			outputFile << "Mrs. ";
			break;
		case S:
			cout << "Ms. ";
			outputFile << "Ms. ";
			break;
		case D:
			cout << "Ms. ";
			outputFile << "Ms. ";
			break;
		default:
			break;
		}
	}
	return m;
}

// This function opens the input file.
void OpenInputFile()
{
	nameData.open("mp6Names.txt");
	if (nameData.fail())
	{
		cout << "Failed to open input file";
		return;
	}
}

// This function opens the output file.
void OpenOutputFile()
{
	outputFile.open("MP6Output.txt");
	if (outputFile.fail())
	{
		cout << "Failed to open output file";
		return;
	}
}
