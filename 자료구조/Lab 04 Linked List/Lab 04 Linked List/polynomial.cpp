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
};

//c: coefficient, d: degree
void addTerm(List<PolyNode>* list, int c, int d) {
    
}

//���׽� ��� �Լ�
void showPolynomial(List<PolyNode>& list) {
    
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

