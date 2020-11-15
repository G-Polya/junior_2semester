#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void showArray(string list[], int count)
{
	cout << "\nThere are " << count << " employees" << endl;
	for (int i = 0; i < count; i++)
		cout << list[i] << endl;
	cout << endl;
}

int main()
{

	
	string in_line;
	ifstream in;
	in.open("test.txt");
	int count = 0;
	while (getline(in, in_line))
	{
		count++;
		//cout << in_line << endl;
	}
		
	in.close();

	in.open("test.txt");
	string* nameList = new string[count];
	for (int i = 0; i < count; i++)
	{
		getline(in, nameList[i]);
		//cout << nameList[i] << endl;
	}
	in.close();

	showArray(nameList, count);

	cout << "�����Ϸ��� �̸��� �Է��Ͻÿ� : ";
	getline(cin, in_line);

	int loc = 0;
	for (int i = 0; i < count; i++)
	{
		if (nameList[loc] != in_line)
			loc++;

	
	}
	
	cout << endl;
	if (nameList[loc] == in_line)
	{
		nameList[loc] = nameList[count - 1];
		count--;
	}
	else
		cout << "�������� �ʴ� �̸��Դϴ�" << endl;
	cout << endl;
	
	showArray(nameList, count);

	
	
}