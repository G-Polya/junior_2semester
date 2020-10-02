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
void Person::getAll(string& name, string& phoneNumber, string& birthday)
{
	name = this->name;
	phoneNumber = this->phoneNumber;
	birthday = this->birthday;
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
void Person::setAll(string name, string phoneNumber, string birthday)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->birthday = birthday;
}

void Person::printAll()
{
	cout << name << endl;
	cout << phoneNumber << endl;
	cout << birthday << endl;
}


ostream& operator<<(ostream& out, Person& person)
{
	out << person.getName() << " " << person.getPhoneNumber() << " " << person.getBirthday() << endl;
	//out << 14 << endl;
	return out;
}

