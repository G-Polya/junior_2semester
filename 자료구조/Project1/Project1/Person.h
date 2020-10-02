#pragma once
#include <iostream>
#include <string>
using namespace std;
class Person
{
private:
	string name;
	string phoneNumber;
	string birthday;

public:
	Person()
	{}
	Person(string name, string phoneNumber, string birthday);

	~Person()
	{}

	// getter
	string getName();
	string getPhoneNumber();
	string getBirthday();
	void getAll(string& name, string& phoneNumber, string& birthday);

	// setter
	void setName(string name);
	void setPhoneNumber(string phoneNumber);
	void setBirthday(string birthday);
	void setAll(string name, string phoneNumber, string birthday);

	void printAll();

	friend ostream& operator<<(ostream& out, Person& person);
	
	

};