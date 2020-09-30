#pragma once
#include <string>
using namespace std;
class Month
{
private:
	int month; // 1, 2, 3...
	string monthName;	// January, Feburary, ...
	int numberOfmonth = 0;	// January의 개수, Feburary의 개수, ...
public:
	Month()
	{ }

	Month(int month, string monthName, int numberOfmonth);
	Month(int month);

	void setAll(int month, string monthName, int numberOfmonth);
	void setMonth(int month);
	void setName(string monthName);
	void setNumber(int numberOfmonth);

	void getAll(string& monthName, int& numberOfmonth);
	int getMonth();
	string getName();
	int getNumber();

	

};