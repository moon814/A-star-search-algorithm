//-----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef NODE_H
#define NODE_H

#include <string>

namespace Azul
{
	class Node
	{
	public:
		Node();
		Node(int x_pos,
			int y_pos,
			std::string nodeName,
			Node* pUpNode,
			Node* pDownNode,
			Node* pRightNode,
			Node* pLeftNode);
		~Node();

		// Data
		bool isNodeBlocked;
		bool isNodeVisited;
		float globalGoal;
		float localGoal;
		Node* parentNode;
		int x_pos;
		int y_pos;
		std::string nodeName;
		Node* pUpNode;
		Node* pDownNode;
		Node* pRightNode;
		Node* pLeftNode;

		
		// Goal: Connect the main node to its 4 adjacent nodes
		void connectNode(Node* _pUpNode,
					Node* _pDownNode,
					Node* _pRightNode,
					Node* _pLeftNode);

	private:
		
	};

}

#endif

// ---  End of File ---
