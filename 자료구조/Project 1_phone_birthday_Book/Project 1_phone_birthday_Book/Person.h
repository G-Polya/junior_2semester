#pragma once
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
	
	// setter
	void setName(string name);
	void setPhoneNumber(string phoneNumber);
	void setBirthday(string birthday);

	
	
};