#include "Month.h"
Month::Month(int month,string monthName, int numberOfmonth)
{
	this->month = month;
	this->monthName = monthName;
	this->numberOfmonth = numberOfmonth;
}



Month::Month(int month)
{
	this->month = month;

	switch (month)
	{
	case 1:
		this->monthName = "January";
		break;
	case 2:
		this->monthName = "Feburary";
		break;
	case 3:
		this->monthName = "March";
		break;
	case 4:
		this->monthName = "April";
		break;
	case 5:
		this->monthName = "May";
		break;
	case 6:
		this->monthName = "June";
		break;
	case 7:
		this->monthName = "July";
		break;
	case 8:
		this->monthName = "August";
		break;
	case 9:
		this->monthName = "September";
		break;
	case 10:
		this->monthName = "October";
		break;
	case 11:
		this->monthName = "November";
		break;
	case 12:
		this->monthName = "December";
		break;

	}
}

void Month::setAll(int month,string monthName, int numberOfmonth)
{
	this->month = month;
	this->monthName = monthName;
	this->numberOfmonth = numberOfmonth;
}

void Month::setMonth(int month)
{
	this->month = month;
}

void Month::setName(string monthName)
{
	this->monthName = monthName;
}

void Month::setNumber(int numberOfmonth)
{
	this->numberOfmonth = numberOfmonth;
}

void Month::getAll(string& monthName, int& numberOfmonth)
{
	monthName = this->monthName;
	numberOfmonth = this->numberOfmonth;
}

int Month::getMonth()
{
	return month;
}

string Month::getName()
{
	return monthName;
}

int Month::getNumber()
{
	return numberOfmonth;
}