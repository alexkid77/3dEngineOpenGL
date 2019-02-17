#include "tree.h"

/***************************************************************************/
/**	\file  tree.cpp
	\brief The CNode class implementation                                  */


/***************************************************************************/
/** is this node the first child?
****************************************************************************/
bool CNode::IsFirstChild()
{
	if (parentNode)
		return (parentNode->childNode == this);
	else
		return false;
}


/***************************************************************************/
/** is this node the last child?
****************************************************************************/
bool CNode::IsLastChild()
{
	if (parentNode)
		return (parentNode->childNode->prevNode == this);
	else
		return false;
}


/***************************************************************************/
/** attach this node to a parent node
****************************************************************************/
void CNode::AttachTo(CNode *newParent)
{
	// if this node is already attached to another node, then detach
	if (parentNode)
		Detach();

	parentNode = newParent;

	if (parentNode->childNode)
	{
		prevNode = parentNode->childNode->prevNode;
		nextNode = parentNode->childNode;
		parentNode->childNode->prevNode->nextNode = this;
		parentNode->childNode->prevNode = this;
	}
	else
	{
		parentNode->childNode = this;		// this is the first child
	}
}


/***************************************************************************/
/** attach a child to this node
****************************************************************************/
void CNode::Attach(CNode *newChild)
{
	// if the child node is already attached, then detach it
	if (newChild->HasParent())
		newChild->Detach();

	newChild->parentNode = this;

	if (childNode)
	{
		newChild->prevNode = childNode->prevNode;
		newChild->nextNode = childNode;
		childNode->prevNode->nextNode = newChild;
		childNode->prevNode = newChild;
	}
	else
		childNode = newChild;
}


/***************************************************************************/
/** detach node from parent
****************************************************************************/
void CNode::Detach()
{
	// if this node is the first child of the parent (first in list)
	// then the parent points to the next child in the list
	if (parentNode && parentNode->childNode == this)
	{
		if (nextNode != this)
			parentNode->childNode = nextNode;
		else
			parentNode->childNode = NULL;		// no next child
	}

	// get rid of links
	prevNode->nextNode = nextNode;
	nextNode->prevNode = prevNode;

	// now this node is not in the list
	prevNode = this;
	nextNode = this;
}


/***************************************************************************/
/** count the number of nodes
****************************************************************************/
int CNode::CountNodes()
{
	if (childNode)
		return childNode->CountNodes() + 1;
	else
		return 1;
}


/***************************************************************************/
/** constructor
****************************************************************************/
CNode::CNode()							// setup node
{
	parentNode = childNode = NULL;
	prevNode = nextNode = this;
}


/***************************************************************************/
/** constructor
****************************************************************************/
CNode::CNode(CNode *node)
{
	parentNode = childNode = NULL;	// setup and attach this node to node
	prevNode = nextNode = this;
	AttachTo(node);
}


/***************************************************************************/
/** destructor
****************************************************************************/
CNode::~CNode()
{
	Detach();				// detach from hierarchy

	while (childNode)		// delete all children
	{
		delete childNode;
	}
}

