// 2016112158 김희수
#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
	this->dataItem = nodeData;
	this->next = nextPtr;
	friendList = new List<DT>();

}


template<class DT>
List<DT>::List(int ignored)
{
	head = NULL;
//	head->next = NULL;
	cursor = head;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
	clear();
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
	
	if (isFull())
	{	
		cout << "List is Full" << endl;
	}
	else
	{
		ListNode<DT>* newNode = new ListNode<DT>(newData, NULL);

		if (head == NULL)
		{
			head = newNode;
			cursor = head;
		}
		else
		{
			if (cursor->next != NULL)		// cursor가 List의 끝이 아닐 경우
			{
				newNode->next = cursor->next;
				cursor->next = newNode;
				cursor = newNode;
			}
			else                           // cursor가 List의 끝일 경우
			{
				cursor->next = newNode;
				cursor = newNode;
			}

		}
	}
		

	//showStructure();
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
	ListNode<DT>* tempNode = cursor;
	if (isEmpty())
	{
		cout << "List is Empty" << endl;
	}
	else
	{
		if ((cursor == head) && (cursor->next == NULL))		// 커서가 head이고 다음 노드가 없음
		{
			cursor = NULL;
			head = NULL;
		}
		else if (cursor == head)							// 커서가 head이고 다음 노드 있음
		{
			gotoNext();
			head = cursor;
		}
		else
		{
			gotoPrior();
			cursor->next = tempNode->next;
			if (tempNode->next != NULL)
				gotoNext();
			else
				gotoBeginning();
		}
	}

	delete tempNode;
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
	if (!isEmpty())
		cursor->dataItem = newData;
	else
		cout << "List is Empty" << endl;
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
	gotoEnd();
	while (!isEmpty())
		remove();
}

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
	return (head == NULL);
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
	ListNode<DT>* tempNode = new ListNode<DT>();
	if (tempNode == NULL)
		return true;
	else
	{
		delete tempNode;
		return false;
	}
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
	if (!isEmpty())
		cursor = head;
	else
		cout << "List is Empty" << endl;
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
	if (!isEmpty())
		while (cursor->next)
			cursor = cursor->next;
	else
		cout << "List is Empty" << endl;
}


//------------------------------------------------

template<class DT>
bool List<DT>::gotoNext()
{
	if (!isEmpty())
	{
		if (cursor->next != NULL)
		{
			cursor = cursor->next;
			return true;
		}
		else
			return false;
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}
	
}

template<class DT>
bool List<DT>::hasNext()
{
	if (!isEmpty())
	{
		if (cursor->next != NULL)
		{
			// cursor = cursor->next;
			return true;
		}
		else
			return false;
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}

}



//------------------------------------------------


//------------------------------------------------

template<class DT>
bool List<DT>::gotoPrior()
{
	ListNode<DT>* tempNode = head;
	if (!isEmpty())
	{
		if (cursor == head)
			return false;
		else
		{
			while (tempNode->next != cursor)
				tempNode = tempNode->next;

			cursor = tempNode;
		}
		return true;
	}
	else
	{
		cout << "List is Empty" << endl;
		return false;
	}


}

//------------------------------------------------


template<class DT>
DT& List<DT>::getCursor() const
{
	if (!isEmpty())
	{
		return cursor->dataItem;
	}
}



template<class DT>
void List<DT>::showStructure() const
{
	
	// cout<<"Loc: " << getCursorloc() << endl;
	if (isEmpty())
	{
		cout << "Empty List" << endl;
	}
	else
	{
		for (ListNode<DT>* iter = head; iter != NULL; iter = iter->next)
			cout << iter->dataItem << " ";


		cout << endl;

		for (auto iter = head; iter != cursor->next; iter = iter->next)
		{
			if (iter != cursor)
				cout << "  ";
			else if (iter == cursor)
				cout << "^";
		}
		cout << endl;


	}

}

//------------------------------------------------

//use in-lab
template<class DT>
void List<DT>::insertBefore(const DT& newElement) {
    if (cursor == head) {
        ListNode<DT>* node = new ListNode<DT>(newElement, head);
        head = node; cursor = node;
    }
    else {
		gotoPrior();
		
        insert(newElement);
    }
}


template<class DT>
bool List<DT>::retrieve(const DT& data)
{
	bool found = false;
	ListNode<DT>* loc = head;

	while (loc != NULL)
	{
		if (loc->dataItem == data)
		{
			cursor = loc;
			found = true;
			break;
		}
		else
			loc = loc->next;
	}
	return found;
}

template<class DT>
void List<DT>::nowFriend(const DT& data1, const DT& data2)
{
	if (data1 == data2)
		return;
	
	if (!retrieve(data1) || !retrieve(data2))
	{
		if (!retrieve(data1))
			cout << "There is no " << data1 << " in the list" << endl;
		else if(!retrieve(data2))
			cout << "There is no " << data2 << " in the list" << endl;
	}
	else if (retrieve(data1) && retrieve(data2))
	{
		retrieve(data1);						// data1을 찾고 그쪽으로 커서이동
		cursor->friendList->insert(data2);		// data2를 data1의 친구로 추가
		retrieve(data2);
		cursor->friendList->insert(data1);		// 같은걸 data2쪽에서 data1에 대해서 수행
		cout << data1 << " is a friend with " << data2 << endl;
	}
}

template<class DT>
void List<DT>::breakFriend(const DT& data1, const DT& data2)
{
	if (data1 == data2)
		return;

	if (!retrieve(data1) || !retrieve(data2))
	{
		if (!retrieve(data1))
			cout << "There is no " << data1 << " in the list" << endl;
		else if (!retrieve(data2))
			cout << "There is no " << data2 << " in the list" << endl;
	}
	else if (retrieve(data1) && retrieve(data2))
	{
		retrieve(data1);						// data1을 찾고 그쪽으로 커서이동
		cursor->friendList->retrieve(data2);	// data1의 친구목록에서 data2을 선택
		cursor->friendList->remove();			// data2를 data1의 친구에서 삭제
		retrieve(data2);
		cursor->friendList->retrieve(data1);
		cursor->friendList->remove();			// 같은걸 data2쪽에서 data1에 대해서 수행
		cout << data1 << " break up with " << data2 << endl;
	}
}

template<class DT>
void List<DT>::printFriends(const DT& data)
{
	ListNode<DT>* person;
	if (retrieve(data))
	{
		person = cursor;
		person->friendList->showStructure();
	}
	else
		cout << "There is no " << data << " in the list" << endl;
}

template<class DT>
void List<DT>::friendCheck(const DT& data1, const DT& data2)
{
	ListNode<DT>* person;
	
	if (data1 == data2)
		return;

	if (!retrieve(data1) || !retrieve(data2))
	{
		if (!retrieve(data1))
			cout << "There is no " << data1 << " in the list" << endl;
		else if (!retrieve(data2))
			cout << "There is no " << data2 << " in the list" << endl;
	}
	else if (retrieve(data1))
	{
		person = cursor;
		if (person->friendList->retrieve(data2))
			cout << "Yes. They are friends" << endl;
		else
			cout << "No. They are not friends" << endl;
	}
}