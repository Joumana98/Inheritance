#include <iostream>

using namespace std;

class clockType
{
public:
	// throw errors
	class Invalid {};

	// constructors 
	clockType();
	clockType(int, int, int);

	// accessors
	void getTime(int&, int&, int&) const;
	void printTime() const;
	bool equalTime(const clockType&);


	//mutators
	void setTime(int, int, int);
	void incrementHr();
	void incrementMin();
	void incrementSec();

private:
	int hr;
	int min;
	int sec;
};

class extClockType : public clockType
{
public:

	// throw Error
	class Invalid {};

	// construtors
	extClockType();
	extClockType(int, int, int, string);

	// accessors
	string getTimeZone() const;
	void print() const;

	//mutators
	void setTimeZone(string t);

private:
	string timeZone;
};

//-----------------------------------------------------------------------------------------------------------

extClockType readTime()
{
	int h, m, s;
	string t;
	char c;
	cout << "Enter time in the following format h:m:s followed by time zone: ";
	cin >> h >> c >> m >> c >> s;
	cin >> t;
	cout << endl;

	return extClockType{ h,m,s,t };

}

int main()
try {

	extClockType c1 = readTime();
	extClockType c2 = readTime();

	c1.print();
	cout << endl;
	c2.print();
	cout << endl;

	c1.incrementSec();
	cout << "After incremeting seconds, c1: ";
	c1.print();
	cout << endl;

	c2.incrementMin();
	cout << "After incremeting minutes, c2: ";
	c2.print();
	cout << endl;

	return 0;
}
catch (clockType::Invalid)
{
	cerr << "Invalid clockType." << endl;
	return 1;
}

catch (extClockType::Invalid)
{
	cerr << "Invalid time zone." << endl;
	return 1;
}

//--------------------------------------------------------------------------------------------------------

clockType::clockType() : hr{ 0 }, min{ 0 }, sec{ 0 }
{

}

clockType::clockType(int h, int m, int s)
{
	if (h >= 0 && h <= 24)
		hr = h;
	else
		throw Invalid{};
	if (m >= 0 && min <= 59)
		min = m;
	else
		throw Invalid{};
	if (s >= 0 && s <= 59)
		sec = s;
	else
		throw Invalid{};

}

void clockType::getTime(int& h, int& m, int& s) const
{
	h = hr;
	m = min;
	s = sec;

}



void clockType::setTime(int h, int m, int s)
{
	hr = h;
	min = m;
	sec = s;
}

void clockType::printTime() const
{
	if (hr <= 9)
		cout << "0" << hr << ":";
	else
		cout << hr << ":";

	if (min <= 9)
		cout << "0" << min << ":";
	else
		cout << min << ":";

	if (sec <= 9)
		cout << "0" << sec;
	else
		cout << sec;

}

void clockType::incrementSec()
{
	if (sec == 59)
	{
		sec = 0;
		incrementMin();
	}
	else
		sec++;

}
void clockType::incrementMin()
{
	if (min == 59)
	{
		min = 0;
		incrementHr();
	}
	else
		min++;

}
void clockType::incrementHr()
{
	if (hr == 23)
		hr = 0;
	else
		hr++;
}

bool clockType::equalTime(const clockType& cl)
{
	if (hr == cl.hr && min == cl.min && sec == cl.sec)
		return true;
	return false;

}

//---------------------------------------------------------------------------------------------------------

extClockType::extClockType()
{
	timeZone = " ";
}

void extClockType::setTimeZone(string t)
{
	if (!(t[0] == 'G' && t[1] == 'M' && t[2] == 'T') && !(t[0] == 'U' && t[1] == 'T' && t[2] == 'C'))
		throw extClockType::Invalid{};
	if (t[3] != '+' && t[3] != '-')
		throw extClockType::Invalid{};
	for (int i = 4; i < t.size(); i++)
		if (!isdigit(t[i]))
			throw extClockType::Invalid{};
	timeZone = t;
}

extClockType::extClockType(int h, int m, int s, string t) : clockType(h, m, s)
{
	setTimeZone(t);
}

string extClockType::getTimeZone() const
{
	return timeZone;
}

void extClockType::print() const
{
	clockType::printTime();
	cout << " " << timeZone;
}
