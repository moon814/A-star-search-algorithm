//-----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Grid.h"
#include "Node.h"

namespace Azul
{
	Node::Node()
	{

	}

	Node::Node(int _x_pos,
		int _y_pos,
		std::string _nodeName,
		Node* _pUpNode,
		Node* _pDownNode,
		Node* _pRightNode,
		Node* _pLeftNode)
	{
		this->x_pos = _x_pos;
		this->y_pos = _y_pos;
		this->nodeName = _nodeName;
		this->pUpNode = _pUpNode;
		this->pDownNode = _pDownNode;
		this->pRightNode = _pRightNode;
		this->pLeftNode = _pLeftNode;

		this->globalGoal = INFINITY;
		this->localGoal = INFINITY;
		this->isNodeVisited = false;
		this->isNodeBlocked = false;
	}


	Node::~Node() {}

	void Node::connectNode(Node* _pUpNode,
		Node* _pDownNode,
		Node* _pRightNode,
		Node* _pLeftNode)
	{
		this->pUpNode = _pUpNode;
		this->pDownNode = _pDownNode;
		this->pRightNode = _pRightNode;
		this->pLeftNode = _pLeftNode;

	}

}

// ---  End of File ---
