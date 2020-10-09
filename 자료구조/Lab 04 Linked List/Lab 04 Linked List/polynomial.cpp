#include <iostream>
#include <cmath>
#include "listlnk.cpp"

using namespace std;

class PolyNode {
private:
    // Data members
    int coefficient;  //���
    int degree;       //����

public:
    PolyNode() {
        coefficient = 0;
        degree = 0;
    }
    PolyNode(int c, int d) {
        coefficient = c;
        degree = d;
    }

    //��� ��ȯ
    int getCoef() {
        return coefficient;
    }
    
    //���� ��ȯ
    int getDegree() {
        return degree;
    }

    //��� ��ȯ
    void addCoef(int added) {
        coefficient += added;
    }

	friend ostream& operator<<(ostream& out, PolyNode& node)
	{
		out << node.getCoef() << "x^"<<node.getDegree();
		return out;
	}
};

int compareDeg(List<PolyNode>* list, int d)
{
	int cursorDegree = list->getCursor().getDegree();
	bool has = list->hasNext();		// true�� �ڿ� ��尡 ����. false�� ������ ���
	if (!has)
	{
		if (cursorDegree == d)		// Ŀ���� ������ ���ο� ����� ������ ���� ���
			return 1;
		else if (cursorDegree < d)  // Ŀ���� ������ ���ο� ����� �������� ���� ���
			return 2;
		else if (cursorDegree > d)  // Ŀ���� ������ ���ο� ����� �������� Ŭ ���
			return 3;
		else                        // ������ �����ε� degree�� �ٸ���
		{
			return 0;
		}
	}
	
	if (cursorDegree == d)
		return 1;
	else if (cursorDegree < d)     // Ŀ���� ������ ���ο� ����� �������� ���� ���
		return 2;
	else if (cursorDegree > d)     // Ŀ���� ������ ���ο� ����� �������� Ŭ ���
		return 3;
	else
	{
		list->gotoNext();
		compareDeg(list, d);
	}	
}


//c: coefficient, d: degree
void addTerm(List<PolyNode>* list, int c, int d)
{
	PolyNode newNode(c, d);

	if (!list->isEmpty())
	{
		list->gotoBeginning();
		
		
		int compare = compareDeg(list, d);
		
		if (compare == 1)
		{
			list->getCursor().addCoef(c);
		}
		else if(compare == 2)			// Ŀ���� ������ ���ο� ����� �������� ���� ���	//x^2�� x^4
		{
			// list->gotoPrior();
			list->insert(newNode);
		}
		else if (compare == 3)		// Ŀ���� ������ ���ο� ����� �������� Ŭ ���		   // x^2�� x^0
		{
			//list->gotoNext();
			list->insert(newNode);
		}
		else
			list->insert(newNode);
	}
	else
	{
//		PolyNode newNode(c, d);
		list->insert(newNode);
		
		
	}
	
	
}

void recursivePrint(bool& next, List<PolyNode>& list)
{
	if (next)
	{
		if (list.getCursor().getDegree() == 0)
			cout << " + " << list.getCursor().getCoef();
		else if (list.getCursor().getCoef() == 1)
			cout << " + " << "x^" << list.getCursor().getCoef();
		else if (list.getCursor().getCoef() < 0)
		{
			cout << list.getCursor().getCoef() << "x^" << list.getCursor().getDegree();
		}
			
		else
			cout << " + " << list.getCursor().getCoef() << "x^" << list.getCursor().getDegree();		
		
		next = list.gotoNext();
		recursivePrint(next, list);
	}
}

//���׽� ��� �Լ�
void showPolynomial(List<PolyNode>& list)
{
	
	if (!list.isEmpty())
	{
		
		list.gotoBeginning();
		bool next = list.gotoNext();
		if (!next)
			cout << list.getCursor().getCoef() << "x^" << list.getCursor().getDegree() << endl;
		
		
		//cout << next << endl;
		while (next)
		{
			list.gotoBeginning();
			
			cout << list.getCursor().getCoef() << "x^" << list.getCursor().getDegree();
			next = list.gotoNext();
			recursivePrint(next, list);
		
				
			cout << endl;

			
			if (!next)
				break;
		}
			
	}
	else
		cout << "Empty Polynomial" << endl;
}


void main()
{
    List<PolyNode> testList;   // Test list
    int coef, degree;          // List data item
    char cmd;                  // Input command

    do
    {        
        showPolynomial(testList);                     // Output list

        // cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if ( cmd == '+'  ||  cmd == '-')
           cin >> degree >> coef;

        switch ( cmd )
        {
          case '+' :                                  // insert
              addTerm(&testList, coef, degree);
              break;

          case '-' :                                  // remove
              coef *= -1;
              addTerm(&testList, coef, degree);
               break;

          case 'C' : case 'c' :                       // clear
               testList.clear();
               break;

          case 'Q' : case 'q' :                   // Quit test program
               break;

          default :                               // Invalid command
               cout << "Inactive or invalid command" << endl;
        }
    }
    while ( cmd != 'Q'  &&  cmd != 'q' );
}

