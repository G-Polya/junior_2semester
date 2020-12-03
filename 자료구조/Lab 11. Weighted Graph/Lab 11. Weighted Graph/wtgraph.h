//--------------------------------------------------------------------
//
//  Laboratory 13                                          wtgraph.h
//
//  Class declaration for the adjacency matrix implementation of
//  the Weighted Graph ADT
//
//--------------------------------------------------------------------

#include <climits>    // For INT_MAX
#include <new>
#include <stdexcept>
#include <iostream>

using namespace std;

const int defMaxGraphSize = 10,      // Default number of vertices
          vertexLabelLength = 11,    // Length of a vertex label
          infiniteEdgeWt = INT_MAX;  // "Weight" of a missing edge

//--------------------------------------------------------------------

class Vertex
{
  public:

    char label [vertexLabelLength];   // Vertex label
};

//--------------------------------------------------------------------

class WtGraph
{
  public:

    // Constructor
    WtGraph ( int maxNumber = defMaxGraphSize )
        throw ( bad_alloc );

    // Destructor
    ~WtGraph ();

    // Graph manipulation operations
    void insertVertex ( Vertex newVertex )            // Insert vertex
        throw ( logic_error );
    void insertEdge ( char *v1, char *v2, int wt )    // Insert edge
        throw ( logic_error );
    bool retrieveVertex ( char *v, Vertex &vData );
                                                      // Get vertex
    bool getEdgeWeight ( char *v1, char *v2, int &wt )
        throw ( logic_error );                        // Get edge wt.
    void removeVertex ( char *v )                     // Remove vertex
        throw ( logic_error );
    void removeEdge ( char *v1, char *v2 )            // Remove edge
        throw ( logic_error );
    void clear ();                                    // Clear graph

    // Graph status operations
    bool isEmpty () const;                            // Graph is empty
    bool isFull () const;                             // Graph is full

    // Output the graph structure -- used in testing/debugging
	void showStructure() const;

    // In-lab operation
    void computePaths();

  private:

    // Facilitator functions
    int getIndex ( char *v );                  // Converts vertex label to an
                                               //   adjacency matrix index
                                       
    int getEdge ( int row, int col );          // Get edge weight using
                                               //   adjacency matrix indices
    void setEdge ( int row, int col, int wt);  // Set edge weight using
                                               //   adjacency matrix indices

    // In-lab functions
    int getPath(int row, int col);             // Get path weight using
                                               //   path matrix indices
    void setPath(int row, int col, int wt);    // Set path weight using
                                               //   path matrix indices

    // Data members
    int maxSize,          // Maximum number of vertices in the graph
        size;             // Actual number of vertices in the graph
    Vertex *vertexList;   // Vertex list
    int *adjMatrix;       // Adjacency matrix
    int* pathMatrix;      // (In-lab) Path matrix
    
};
