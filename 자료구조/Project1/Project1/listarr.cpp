
// 2016112158 김희수
#include "listarr.h"
#include <iomanip>
using namespace std;

//--------------------------------------------------------------------


List::List(int maxNumber): maxSize(maxNumber), size(0), cursor(-1)
{
	// pre-lab
	dataItems = new Person[maxSize];
	
	for (int i = 0; i < 12; i++)
		monthes[i] = Month(i + 1);

}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;

}

//--------------------------------------------------------------------
void List::insert(const Person& newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{

	// pre-lab
	if (isFull())
	{
		cout << "List is full. You cannot insert" << endl;
		return;
	}

	if (cursor == size - 1)
	{
		cursor++;
		size++;
		dataItems[cursor] = newDataItem;


	}
	else
	{
		cursor = size;
		size++;
		dataItems[cursor] = newDataItem;
	}

	int month = atoi(dataItems[cursor].getBirthday().substr(0, 2).c_str());
	for (int i = 0; i < 12; i++)
	{
		if (monthes[i].getMonth() == month)	// entry가 태어난 월과 monthes 배열안의 month와 비교해서 같으면
		{
			int currentNumber = monthes[i].getNumber();
			monthes[i].setNumber(currentNumber + 1);	// monthes배열안의 원소의 numberOfentry 증가

			//즉, List 안에 들어있는 entry가 태어난 월들이 2,2,4라면
			//monthes안의 원소의 month(2,2,4)와 비교해서 같으면 Feburary, Feburary, April의 numberOfentry를 증가시킨다는 뜻

		}
	}
	
}

//--------------------------------------------------------------------

void List::remove(string name) throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.
{
	// pre-lab
	Person person;
//	int currentCursor;
	for (int i = 0; i < size; i++)
	{
		if (name == dataItems[i].getName())
		{
			person = dataItems[i];
			cursor = i;
		}
	}

	//cout << "Person : " << person.getName() << ", currentCursor : " << currentCursor << endl;

	if (isEmpty())
	{
		cout << "List is empty. You cannot remove" << endl;
		return;
	}
	
	int month = atoi(person.getBirthday().substr(0, 2).c_str());
	for (int i = 0; i < 12; i++)
	{
		if (monthes[i].getMonth() == month)	// entry가 태어난 월과 monthes 배열안의 month와 비교해서 같으면
		{
			int currentNumber = monthes[i].getNumber();
			monthes[i].setNumber(currentNumber - 1);	// monthes배열안의 원소의 numberOfentry 증가

			//즉, List 안에 들어있는 entry가 태어난 월들이 2,2,4라면
			//monthes안의 원소의 month(2,2,4)와 비교해서 같으면 Feburary, Feburary, April의 numberOfentry를 증가시킨다는 뜻

		}
	}

	if (cursor == size - 1)
	{
		cursor--;
		size--;
	}
	else                // 끝에 있는 데이터를 현재 커서 위치에 저장 
	{
		dataItems[cursor] = dataItems[size - 1];
		cursor--;
		size--;
	}

	
}

void List::printCursorSize()
{
	cout << "Cursor : " << cursor << endl;
	cout << "Size : " << size << endl;
}




bool List::isEmpty() const
// Returns 1 if a list is empty. Otherwise, returns 0.
{
	// pre-lab

	return !this->size;
}

//--------------------------------------------------------------------

bool List::isFull() const
// Returns 1 if a list is full. Otherwise, returns 0.
{
	// pre-lab
	if (this->size == this->maxSize)
		return true;
	else
		return false;

}

void List::read()
{
	string fileName;
	cout << "Enter the name of the file: ";
	cin >> fileName;
	fileName = fileName + ".txt";
	//fileName = "FriendFile.txt";
	ifstream fileIn;

	fileIn.open(fileName);

	string s;
	int count = 0;
	if (!fileIn.is_open())
		cout << "파일 열기 실패" << endl;
	else
	{
		while (getline(fileIn, s))
			count++;

		fileIn.close();

		
	}
	
	fileIn.open(fileName);
	if (!fileIn.is_open())
		cout << "파일 열기 실패" << endl;
	else
	{
		string* stringList = new string[count];
		int i = 0;

		while (getline(fileIn, s))
			stringList[i++] = s;
		fileIn.close();

		int numberOfentry = (count + 1) / 4;	// 4는 이름, 전화번호, 생일, 그리고 \n하나를 의미한다 
		cout << "Total number of entries in the list: " << numberOfentry << endl;
		for (int i = 0; i < numberOfentry; i++)
			insert(Person(stringList[0 + 4 * i], stringList[1 + 4 * i], stringList[2 + 4 * i]));
		
		
	}
}

void List::printSummary()
{


	cout << "Number of birthdays in the list: "<<size << endl;
	for (int i = 0; i < 12; i++)
	{
		int numberOfmonth = monthes[i].getNumber();
		if (numberOfmonth != 0)
		{
			cout << monthes[i].getName() << " : " << monthes[i].getNumber() << endl;
		}
	}
}

string List::getNamefromMonth(int month)
{
	string name;
	for (int i = 0; i < 12; i++)
	{
		if (monthes[i].getMonth() == month)
			name = monthes[i].getName();
	}

	return name;
}

int List::getMonthfromName(string name)
{
	int month;
	for (int i = 0; i < 12; i++)
	{
		if (monthes[i].getName() == name)
			month = monthes[i].getMonth();
	}
	return month;
}

int List::getBirthdays(string name)
{
	int birthdayNum;
	for (int i = 0; i < 12; i++)
	{
		if (monthes[i].getName() == name)
			birthdayNum = monthes[i].getNumber();
	}
	return birthdayNum;
}


void List::select()
{
	string monthName;
	cout << "Enter the selected month: ";
	cin >> monthName;
	//monthName = "January";
	cout << "Total number of birthdays in " + monthName + " : " << getBirthdays(monthName) << endl;
	for (int i = 0; i < size; i++)
	{
		int month = atoi(dataItems[i].getBirthday().substr(0, 2).c_str());		// List안에 들어있는 entry가 태어난 월

		if (month == getMonthfromName(monthName))
		{
			dataItems[i].printAll();
			cout << endl;
		}
	}
}

void List::write()
{
	string fileName;
	//fileName = "FriendFileUpdate.txt";
	cout << "Enter the name of the file: ";
	cin >> fileName;
	cout << "The list is written into " << fileName << endl;
	fileName = fileName + ".txt";
	ofstream fileOut;
	fileOut.open(fileName);

	if (fileOut.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			fileOut << dataItems[i].getName() << endl;
			cout << dataItems[i].getName() << endl;

			fileOut << dataItems[i].getPhoneNumber() << endl;
			cout << dataItems[i].getPhoneNumber() << endl;

			fileOut << dataItems[i].getBirthday() << endl;
			cout << dataItems[i].getBirthday() << endl;

			fileOut << endl;
			cout << endl;		
		}
		
	}
	else
		cout << fileName <<" 파일 연결 실패" << endl;

	

	fileOut.close();

}

void List::printList()
{
	for (int i = 0; i < size; i++)
	{
		dataItems[i].printAll();
		cout << endl;
	}
}
