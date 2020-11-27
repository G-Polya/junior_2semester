#include <iostream>
#include <string>
#include "bstree.cpp"
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

// remove '\n'
string removeLF(string str)
{
	while (true)
	{
		int loc = str.find('\n');
		string sub = str.substr(loc + 1, str.length() - 1);
		if (sub.length() == 0)
			break;

		//cout << sub.length() << endl;
		//cout << loc << endl;
		str = str.substr(0, loc) + sub;
		//cout << str << endl;
	}
	
	return str;
}

void main()
{
	

	BSTree<TestData, char> testTree;
	TestData testData;
	string str;
	getline(cin, str, '*');
	str = removeLF(str);

	
	
	for (int i = str.length()-1; i >=0; i--)
	{
		testData.setKey(str[i]);
		testTree.insert(testData);
	}
	


	//testTree.showStructure();

	testTree.preOrder();
	cout << endl;
	




	
}
