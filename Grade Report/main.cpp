#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "studentType.h"

using namespace std;

void getStudentData(ifstream& inFile, studentType students[], int nb);
void printGradeReport(ofstream& outFile, studentType students[], int studentNb, double tuitionRate);

int main()
{
	ofstream outFile;
	ifstream inFile;

	inFile.open("C:\\inData.txt");
	if (!inFile)
	{
		cout << "File is not found!" << endl;
		cout << "Program terminated." << endl;
		return 1;
	}
	outFile.open("C:\\outData.txt");

	// process a max of 10 students
	studentType list[10];

	// read from the first line of the input file
	int studentsNo;
	double tuitionRate;

	inFile >> studentsNo >> tuitionRate;
	getStudentData(inFile, list, studentsNo);
	printGradeReport(outFile, list, studentsNo, tuitionRate);

	return 0;
}

void getStudentData(ifstream& inFile, studentType students[], int nb)
{
	string first, last;
	int ID;
	char paid;
	bool isPaid;
	int coursesNb;

	string name;
	string cID;
	int credit;
	char g;

	courseType c[6];

	char grades[6];

	for (int i = 0; i < nb; i++)
	{
		inFile >> first >> last >> ID >> paid >> coursesNb;

		if (paid == 'Y')
			isPaid = true;
		else
			isPaid = false;

		for (int j = 0; j < coursesNb; j++)
		{
			inFile >> name >> cID >> credit >> g;
			c[j].setCourseInfo(name, cID, credit);
			grades[j] = g;
		}
		students[i].setInfo(first, last, ID, isPaid, coursesNb, c, grades);
	}

}

void printGradeReport(ofstream& outFile, studentType students[], int studentNb, double tuitionRate)
{
	for (int i = 0; i < studentNb; i++)
		students[i].print(outFile, tuitionRate);
}
