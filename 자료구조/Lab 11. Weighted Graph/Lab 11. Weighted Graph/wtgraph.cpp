//--------------------------------------------------------------------
//
//  Laboratory 14                                          wtgraph.cpp
//
//  Implementation of the Weighted Graph ADT
//
//--------------------------------------------------------------------
#include "wtgraph.h"

//--------------------------------------------------------------------

WtGraph::WtGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize * maxSize];
	pathMatrix = new int[maxSize*maxSize];

	for (int i = 0; i < maxSize * maxSize; i++)
	{
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}
}

WtGraph::~WtGraph()
{
	delete[] vertexList, adjMatrix, pathMatrix;
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)
{
	string str = v;
	for (int i = 0; i < size; i++)
	{
		if (str == vertexList[i].label)
			return i + 1;
	}

	cout << "The correct vertex doesn't exist" << endl;
	return 0;

}

int WtGraph::getEdge(int row, int col)
{
	int index = row * maxSize + col;
	return adjMatrix[index];
}

void WtGraph::setEdge(int row, int col, int wt) 
{
	int index = row * maxSize + col;
	adjMatrix[index] = wt;
}

//--------------------------------------------------------------------

void WtGraph::insertVertex(Vertex newVertex)
{
	if (isFull())
		cout << "Graph is Full" << endl;
	else
	{
		string str = newVertex.label;
		for(int i =0; i<size;i++)
			if (str == vertexList[i].label)
			{
				vertexList[i] = newVertex;
				return;
			}
		vertexList[size] = newVertex;
		size++;

	}
}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
	if (wt > 0 && wt < infiniteEdgeWt && getIndex(v1) && getIndex(v2))
	{
		int v1Index = getIndex(v1) - 1, v2Index = getIndex(v2) - 1;
		setEdge(v1Index, v2Index, wt);
		setEdge(v2Index, v1Index, wt);
	}
	
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
	string str = v;
	for (int i = 0; i < size; i++)
	{
		if (str == vertexList[i].label)
			return true;
	}
	return false;
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
	if (getIndex(v1) && getIndex(v2))
	{
		int v1Index = getIndex(v1) - 1, v2Index = getIndex(v2) - 1;
		wt = getEdge(v1Index, v2Index);
		return true;
	}
}

//--------------------------------------------------------------------

void WtGraph::removeVertex(char* v)
{
	if (isEmpty())
		cout << "Graph is Empty" << endl;
	else
	{
		int rmIndex = getIndex(v) - 1;
		if (rmIndex != -1)
		{
			for (int i = rmIndex; i < size-1; i++)
				vertexList[i] = vertexList[i + 1];
			
			for (int i = 0; i < size; i++)
			{
				for (int j = rmIndex; j < size-1; j++)
					setEdge(i, j, getEdge(i, j + 1));
			}

			for (int i = 0; i < size; i++)
			{
				for (int j = rmIndex; j < size - 1; j++)
					setEdge(j, i, getEdge(j + 1, i));
			}
			size--;

		}
	}
	
}

void WtGraph::removeEdge(char* v1, char* v2)
{
	int v1Index = getIndex(v1) - 1, v2Index = getIndex(v2) - 1;
	if (v1Index != -1 && v2Index != -1)
	{
		setEdge(v1Index, v2Index, infiniteEdgeWt);
		setEdge(v2Index, v1Index, infiniteEdgeWt);
	}
	
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
	for (int i = 0; i < maxSize * maxSize; i++)
	{
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}
	size = 0;
}

bool WtGraph::isEmpty() const
{
	return (size == 0);
}

bool WtGraph::isFull() const
{
	return (size == maxSize);
}

//--------------------------------------------------------------------

void WtGraph::showStructure() const

// Outputs a graph's vertex list, adjacency matrix, and path matrix.
// This operation is intended for testing/debugging purposes only.

{
	int wt,         // Edge weight
		row, col;   // Loop counters

	if (isEmpty())
		cout << "Graph is Empty" << endl;
	else
	{
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++)
			cout << row << '\t' << vertexList[row].label << endl;

		cout << endl << "Edge matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = adjMatrix[row * maxSize + col];
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}

		cout << endl << "Path matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = pathMatrix[row*maxSize+col];
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}
	}
}
//--------------------------------------------------------------------


 int WtGraph::getPath(int row, int col)
 {
	 return (pathMatrix[row * maxSize + col]);
 }

 void WtGraph::setPath(int row, int col, int wt) 
 {
	 pathMatrix[row * maxSize + col] = wt;
 }

 void WtGraph::computePaths() 
 {
	 if (isEmpty())
		 cout << "Graph is Empty" << endl;
	 else
	 {
		 int i = 0, j = 0, k = 0;
		 int matrixSize = maxSize * maxSize;

		 for (i = 0; i < matrixSize; i++)
			 pathMatrix[i] = adjMatrix[i];

		 for (i = 0; i < size; i++)
			 for (j = 0; j < size; j++)
				 for (k = 0; k < size; k++)
					 if (getPath(j, i) != infiniteEdgeWt)
						 if (getPath(i, k) != infiniteEdgeWt)
							 if(i != j && j!=k && k!= i)
								 if ((unsigned long long)(getPath(j, i) + getPath(i, k)) < getPath(j, k))
									 setPath(j, k, getPath(j, i) + getPath(i, k));

	 }
 }