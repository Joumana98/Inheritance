#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


using namespace std;

// University has students
// Every student takes courses

class courseType
{
public:
	//constructor with default parameters
	courseType(string = "", string = "", int = 0);

	//accessors
	void print(ostream&) const; // sends output information to the output device passed as a parameter
	string getCourseName() const;
	int getCourseCredits() const;
	string getCourseNo() const;


	//mutators
	void setCourseInfo(string, string, int);

private:
	string courseName;
	string courseNo;
	int courseCredits;
};

class personType
{
public:
	void print() const;
	string getFirstName() const;
	string getLastName() const;
	bool nameIsEqual(const personType& person) const;
	bool lastIsEqual(const personType& person) const;

	void setName(string, string);
	void setFirstName(string);
	void setLastName(string);

	personType(string = "", string = "");


private:
	string firstName;
	string middleName;
	string lastName;
};

// every student is a person
// every student has courses
class studentType : public personType // public inheritance
{
public:
	// constructor
	studentType();

	//accessors
	void print(ostream& outF, double tuitionRate); //overrided function
	// if the actual parameter corresponding to outF is the object cout, th output is shown n the standard output device
	// if the actual parameter corresponding to outF is an ofstream object, the output goes to th file specified by that object
	int getHoursEnrolled() const; // return the number of credir hours student is enrolled in
	double getGpa() const;
	double billingAmount(double tuitionRate) const;

	//mutators
	void setInfo(string, string, int, bool, int, courseType[], char[]);


private:
	void sortCourses(); // sort the array coursesEnrolled and adjust the array courseGrade
	// only needed for internal data manipulation

	int sID;
	bool isTuitionPaid;
	int numberOfCourses;
	courseType  coursesEnrolled[6]; // composition
	char courseGrade[6];
};
