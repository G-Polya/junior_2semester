#include <iostream>
#include "stackarr.cpp"
#include "queuearr.h"
using namespace std;

void showArray(string list[], int count)
{
	for (int i = 0; i < count; i++)
		cout << list[i] << endl;
	cout << endl;
}

int main()
{

	
	cout << "Enter 0 to stop" << endl;
	int maxString;

	do
	{
		
		cin >> maxString;
		string* stringList = new string[maxString];
		
		for (int i = 0; i < maxString; i++)
		{
			string temp;
			cin >> temp;
			stringList[i] = temp;
		}
		showArray(stringList, maxString);

		cout << "string input end" << endl;

		int mismatches = 0;
		
		for (int i = 0; i < maxString; i++)
		{
			Stack<char> s(stringList[i].length());
			Queue<char> q(stringList[i].length());
			for (int i = 0; i < stringList[i].length(); i++)
			{
				s.push(stringList->at(i));
				q.enqueue(stringList->at(i));
			}
			
			while (!q.isEmpty() && !s.empty())
			{
				char qitem = q.dequeue();
				char sitem = s.pop();
				if (sitem != qitem)
					mismatches++;
			}



		}

	}  while (maxString != 0);
	

}