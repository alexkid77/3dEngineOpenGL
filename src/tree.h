/**************************************************************************/
/**	\file  tree.h
	\brief The CNode class

	\author Kevin Hawkins
	\date   3/29/2001
***************************************************************************/

#ifndef __TREE_H
#define __TREE_H

#ifndef NULL
#define NULL 0L
#endif


/**************************************************************************/
/** \class CNode
	\brief The CNode class represents a single node in the 
		   cyclic linked list tree that holds all objects
		   in the game.
***************************************************************************/
class CNode
{
public:
	// data
	CNode *parentNode;	// parent node
	CNode *childNode;	// child node
	CNode *prevNode;	// previous node
	CNode *nextNode;	// next node


	bool HasParent() { return (parentNode != NULL); }	// does node have a parent?
	bool HasChild() { return (childNode != NULL); }	    // does node have a child?

	// is this node the first child?
	bool IsFirstChild();

	// is this node the last child?
	bool IsLastChild();

	// attach this node to a parent node
	void AttachTo(CNode *newParent);

	// attach a child to this node
	void Attach(CNode *newChild);

	// detach node from parent
	void Detach();

	// count the number of nodes
	int CountNodes();

	// constructor
	CNode();                // setup node

	// constructor
	CNode(CNode *node);

	// destructor
	virtual ~CNode();
};


#endif
