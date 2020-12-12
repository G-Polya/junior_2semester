#include "bstree.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

void main()
{
	Tree company;
	string str;
	string str_arr[3];

	while (true)
	{
		if (company.isEmpty())
		{
			cout << "CEO : ";
			cin >> str;
			company.setCEO(str);
			cin.ignore();
		}
		else
		{
			getline(cin, str);

			char* str_buff = new char[100];
			char* context = new char[100];
			strcpy_s(str_buff, 100, str.c_str());
			int str_count = 0;

			char* tok = strtok_s(str_buff, " ", &context);
			while (tok != NULL)
			{
				str_arr[str_count++] = string(tok);
				tok = strtok_s(NULL, " ", &context);
			}

			if (str_arr[1] == "Hires" || str_arr[1] == "hires")
				company.hire(str_arr[0], str_arr[2]);
			else if (str_arr[0] == "Fire" || str_arr[0] == "fire")
			{
				if (company.fire(str_arr[1]))
					cout << str_arr[1] << " is fired" << endl;
				else
					cout << "There is not " << str_arr[1] << " in this company" << endl;
			}
			else if (str_arr[0] == "Print" || str_arr[0] == "print")
				company.print();
			else if (str_arr[0] == "Clear" || str_arr[0] == "clear")
				company.clear();
			else if (str_arr[0] == "Q" || str_arr[0] == "q")
				break;
			else cout << "invalid command" << endl;

			for (int i = 0; i < 3; i++)
				str_arr[i] = "";
			
		}
		
	}
}