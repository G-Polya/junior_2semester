#include <iostream>
#include <string>
#include "bstree.cpp"
#include <cstring>

//#include "exprtree.h"    //pre-lab
//#include "logitree.h"  //in-lab1

using namespace std;

class TestData
{
public:
	void setKey(char newKey)
	{
		keyField = newKey;
	}

	char key() const
	{
		return keyField;
	}

private:
	char keyField;
};

//// remove '\n'
//string removeLF(string str)
//{
//	while (true)
//	{
//		int loc = str.find('\n');
//		string sub = str.substr(loc + 1, str.length() - 1);
//		if (sub.length() == 0)
//			break;
//
//		//cout << sub.length() << endl;
//		//cout << loc << endl;
//		str = str.substr(0, loc) + sub;
//		//cout << str << endl;
//	}
//	
//	return str;
//}

bool hasEnd(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '$')
			return true;

	}
}

template<class TE, class KF>
void preOrderAll(BSTree<TE, KF>& testTree, string result)
{
	TestData testData;
	for (int i = result.length() - 1; i >= 0; i--)
	{
		testData.setKey(result[i]);
		testTree.insert(testData);
	}

	cout << "Output: ";
	testTree.preOrder();
	cout << endl;
}


void main()
{
	while (true)
	{
		BSTree<TestData, char> testTree;
		string str;
		string result = "";

		do
		{
			cin >> str;
			result += str;
		} while ((str != "$") && (str != "*"));

		bool endFlag = hasEnd(str);

		if (endFlag == 1)
		{
			int loc = result.find('$');
			result = result.substr(0, loc) + result.substr(loc + 1, result.length() - 1);



			preOrderAll(testTree, result);

			cout << endl;
			break;
		}
		else
		{

			int loc = result.find('*');
			result = result.substr(0, loc) + result.substr(loc + 1, result.length() - 1);

			preOrderAll(testTree, result);

			testTree.clear();
		}

	}
}
