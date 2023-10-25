#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "studentType.h"

using namespace std;

courseType::courseType(string name, string ID, int credit)
{
	courseName = name;
	courseNo = ID;
	courseCredits = credit;

}


void courseType::print(ostream& outF) const
{
	outF << left << setw(12) << courseNo
		<< left << setw(15) << courseName
		<< right << setw(4) << courseCredits;

}

string courseType::getCourseName() const
{
	return courseName;

}

int courseType::getCourseCredits() const
{
	return courseCredits;
}

string courseType::getCourseNo() const
{
	return courseNo;
}

void courseType::setCourseInfo(string name, string ID, int credit)
{
	courseName = name;
	courseNo = ID;
	courseCredits = credit;
}

//----------------------------------------------------------------------------------------------------------

void personType::print() const
{
	cout << firstName << " " << lastName;
}

void personType::setName(string first, string last)
{
	firstName = first;
	lastName = last;
}

string personType::getFirstName() const
{
	return firstName;
}


string personType::getLastName() const
{
	return lastName;
}

personType::personType(string first, string last)
{
	firstName = first;
	lastName = last;
}

void personType::setFirstName(string first)
{
	firstName = first;
}

void personType::setLastName(string last)
{
	lastName = last;
}

bool personType::nameIsEqual(const personType& person) const
{
	if (firstName == person.firstName)
		return true;
	else
		return false;

}

bool personType::lastIsEqual(const personType& person) const
{
	if (lastName == person.lastName)
		return true;
	else
		return false;

}

//-----------------------------------------------------------------------------------------------------------

void studentType::setInfo(string first, string last, int ID, bool isPaid, int coursesNb, courseType c[], char g[])
{
	setName(first, last);
	sID = ID;
	isTuitionPaid = isPaid;
	numberOfCourses = coursesNb;
	for (int i = 0; i < coursesNb; i++)
		coursesEnrolled[i] = c[i];
	for (int i = 0; i < coursesNb; i++)
		courseGrade[i] = g[i];
	sortCourses();

}

studentType::studentType()
{
	// default constructor for personType is automatically triggered
	sID = 0;
	isTuitionPaid = false;
	numberOfCourses = 0;
	// default constructor for courseType array is automatically triggered
	for (int i = 0; i < 6; i++)
		courseGrade[i] = '*';


}

void studentType::print(ostream& outF, double tuitionRate)
{
	outF << "Student Name: " << getFirstName() << " " << getLastName() << endl;
	outF << "Student ID: " << sID << endl;
	outF << "Number of courses enrolled: " << numberOfCourses << endl;
	outF << endl;

	outF << left << setw(12) << "Course No"
		<< left << setw(15) << "course Name"
		<< left << setw(10) << "Credits"
		<< left << "Grade" << endl;
	for (int i = 0; i < numberOfCourses; i++)
	{
		coursesEnrolled[i].print(outF);
		if (isTuitionPaid == true)
			outF << left << "        " << courseGrade[i] << endl;
		else
			outF << "       ***" << endl;
	}
	outF << endl;
	outF << "Total Number of credits: " << getHoursEnrolled() << endl;

	outF << fixed << showpoint << setprecision(2);
	if (isTuitionPaid == true)
		outF << "Mid-semester GPA: " << getGpa() << endl;
	else
	{
		outF << "*** Grades are being held for not paying the tuition. ***" << endl;
		outF << "Amount Due: " << billingAmount(tuitionRate) << endl;
	}

	outF << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
}

int studentType::getHoursEnrolled() const
{
	int totalCredits = 0;
	for (int i = 0; i < numberOfCourses; i++)
		totalCredits += coursesEnrolled[i].getCourseCredits();
	return totalCredits;
}
double studentType::getGpa() const
{
	double sum = 0.0;
	for (int i = 0; i < numberOfCourses; i++)
	{
		switch (courseGrade[i])
		{
		case'A':
			sum += coursesEnrolled[i].getCourseCredits() * 4;
			break;

		case'B':
			sum += coursesEnrolled[i].getCourseCredits() * 3;
			break;
		case'C':
			sum += coursesEnrolled[i].getCourseCredits() * 2;
			break;
		case'D':
			sum += coursesEnrolled[i].getCourseCredits() * 1;
			break;
		case'F':
			sum += coursesEnrolled[i].getCourseCredits() * 0;
			break;
		default:
			cout << "Invalid Course Grade." << endl;
		}
	}

	return sum / getHoursEnrolled();

}

double studentType::billingAmount(double tuitionRate) const
{
	// if a student has not paid his tuition, this function calculates and return the amount due

	return tuitionRate * getHoursEnrolled();

}

void studentType::sortCourses()
{
	int minIndex;
	string course1, course2;

	courseType temp;
	char tempGrade;

	// sort by course names
	for (int i = 0; i < numberOfCourses; i++)
	{
		minIndex = i;
		for (int j = i; j < numberOfCourses; j++)
		{
			course1 = coursesEnrolled[minIndex].getCourseName();
			course2 = coursesEnrolled[j].getCourseName();

			if (course2 < course1)
				minIndex = j;
		}
		temp = coursesEnrolled[i];
		coursesEnrolled[i] = coursesEnrolled[minIndex];
		coursesEnrolled[minIndex] = temp;

		//reorder grades
		tempGrade = courseGrade[i];
		courseGrade[i] = courseGrade[minIndex];
		courseGrade[minIndex] = tempGrade;

	}
}