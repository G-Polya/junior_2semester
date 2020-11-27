//--------------------------------------------------------------------
//
//  Laboratory 11                                           bstree.h
//
//  Class declarations for the linked implementation of the Binary
//  Search Tree ADT -- including the recursive partners of the
//  public member functions
//
//--------------------------------------------------------------------
//#include <stdexcept>

using namespace std;

template < class TE, class KF > class BSTree;
template < class TE, class KF > class BSTreeNode;

template < class TE, class KF >
class BSTreeNode             // Facilitator class for the BSTree class
{
private:

	// Constructor
	BSTreeNode(const TE& elem,
		BSTreeNode* leftPtr, BSTreeNode* rightPtr);

	// Data members
	TE element;          // Binary search tree element
	BSTreeNode* left,    // Pointer to the left child
		* right;   // Pointer to the right child

	friend class BSTree<TE, KF>;
};

//--------------------------------------------------------------------

template < class TE, class KF >    // TE : tree element
class BSTree                       // KF : key field
{
public:

	// Constructor
	BSTree();

	// Destructor
	~BSTree();

	// Binary search tree manipulation operations
	void insert(const TE& newElement) // Insert element
		throw (bad_alloc);

	bool retrieve(KF searchKey, TE& searchElement) const;
	// Retrieve element
	bool remove(KF deleteKey);                  // Remove element
	void writeKeys() const;                      // Output keys
	void clear();                                // Clear tree

	// Binary search tree status operations
	bool isEmpty() const;                           // Tree is empty
	bool isFull() const;                            // Tree is full

	// Output the tree structure -- used in testing/debugging
	void showStructure() const;
	void preOrder();

private:
	void preOrderSub(BSTreeNode<TE, KF>*& p);
	// Recursive partners of the public member functions -- insert
	// prototypes of these functions here.
	void insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement);
	bool retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey,
		TE& searchElement) const;
	bool removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey);
	void cutRightmost(BSTreeNode<TE, KF>*& r,
		BSTreeNode<TE, KF>*& delPtr);
	void writeKeysSub(BSTreeNode<TE, KF>* p) const;
	void clearSub(BSTreeNode<TE, KF>* p);
	void showSub(BSTreeNode<TE, KF>* p, int level) const;

	// Data member
	BSTreeNode<TE, KF>* root;   // Pointer to the root node
};