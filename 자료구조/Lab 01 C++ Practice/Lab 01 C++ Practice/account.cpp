// 2016112158 ±èÈñ¼ö 2020.09.10 Á¦Ãâ

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

class bank
{
    char name[20];
    int acno;
    char actype[4];
    float balance;

public:
    void init();
    void deposit();
    void withdraw();
    void disp_det();
};
//member functions of bank class
void bank::init()
{
	balance = 0;
	cout << "Enter the Name of the depsoitor : ";
	cin >> name;

	cout << "Enter the Account Number : ";
	cin >> acno;
	
	cout << "Enter the Account Type : (CURR / SAVG / FD / RD / DMAT) ";
	cin >> actype;

	cout << "Enter the Amount to Deposit : ";
	float amount;
	cin >> amount;
	balance += amount;
	cout << endl;
}
void bank::deposit()
{
	cout << "Enter the amount to deposit : ";
	float amount;
	cin >> amount;
	balance += amount;
	cout << endl;
}
void bank::withdraw()
{
	float amount = 0;
	cout << "Enter the amount to withdraw : ";
	cin >> amount;
	balance -= amount;
	cout << endl;
}
void bank::disp_det()
{
	cout << "Account Details" << endl;
	cout << "Name of the depositor : " << this->name << endl;
	cout << "Account Number        : " << this->acno << endl;
	cout << "Account Type          : " << this->actype << endl;
	cout << "Balance               : $" << int(this->balance) << endl;
	cout << endl;
}
// main function , exectution starts here
void main(void)
{
    // clrscr();
    bank obj;
    int choice = 1;
    while (choice != 0)
    {
        cout << "Enter 0 to exit\n1. Initialize a new acc.\n2. Deposit\n3. Withdraw\n4. See A / c Status\n";
        cin >> choice;
        cin.ignore();
		cout << endl;
        switch (choice)
        {
        case 0:
            obj.disp_det();
			cout << "EXITING PROGRAM." << endl;;
            break;
        case 1:
            obj.init();
            break;
        case 2:
            obj.deposit();
            break;
        case 3:
            obj.withdraw();
            break;
        case 4:
            obj.disp_det();
            break;
        default:
            cout << "Illegal Option" << endl;
        }
    }
    _getch();
}