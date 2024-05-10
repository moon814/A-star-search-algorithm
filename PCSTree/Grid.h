//-----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef GRID_H
#define GRID_H

#include "Node.h"
#include <list>
using namespace std;

namespace Azul
{
	class Grid
	{
	public:
		
		struct Coordinate
		{
			int x;
			int y;
		};
		
		//bool checkIfNodeVisited();
		//int width;
		//int height;
		
	
		int gridWidth_x;
		int gridHeight_y;
		Node* startNode;
		Node* endNode;
		list<Node*> visitedNodeList;
		Node* pHead;

		void createGridManual();
		void createGrid(int _gridWidth_x, int _gridHeight_y);
		bool setStartNode_pos(int x, int y);
		bool setEndNode_pos(int x, int y);
		bool nodePosValid(int x, int y);
		float calcNodeDistance(Node* start, Node* end);
		Node* getNodeFromPos(int x, int y);
		Node* findBestNeighbor(Node* primeNode);
		void findShortestPath();
		void printNodePath() const;

	private:

	};

}

#endif

// ---  End of File ---
