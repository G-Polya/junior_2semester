#include "Person.h"

Person::Person(string name, string phoneNumber, string birthday)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->birthday = birthday;
}

// getter
string Person::getName()
{
	return this->name;
}

string Person::getPhoneNumber()
{
	return this->phoneNumber;
}

string Person::getBirthday()
{
	return this->birthday;
}

// setter
void Person::setName(string name)
{
	this->name = name;
}
void Person::setPhoneNumber(string phoneNumber)
{
	this->phoneNumber = phoneNumber;
}
void Person::setBirthday(string birthday)
{
	this->birthday = birthday;
}