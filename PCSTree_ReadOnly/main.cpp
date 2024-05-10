//-----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Grid.h"
#include "Node.h"

using namespace Azul;

int main()
{
	Trace::out("happy");
	/*
	int gridWidth = 3;
	int gridHeight = 6;

	Grid* grid = new Grid();
	grid->createGrid(gridWidth, gridHeight);
	*/

	Grid* grid = new Grid();
	grid->createGridManual();
	//grid->createGrid(3, 3);

	bool rtnVal;

	rtnVal = grid->setEndNode_pos(0, 2);
	assert(rtnVal);

	rtnVal = grid->setStartNode_pos(0, 0);
	assert(rtnVal);

	

	float nodeDistance = grid->calcNodeDistance(grid->pHead, grid->pHead->pRightNode->pRightNode->pUpNode);
	Trace::out("nodeDistance: %f", nodeDistance);


	bool validPoint;
	validPoint = grid->nodePosValid(1,1);
	Trace::out("data: %d is true \n", validPoint);
	validPoint = grid->nodePosValid(2, 1);
	Trace::out("data: %d is true \n", validPoint);
	validPoint = grid->nodePosValid(2, 2);
	Trace::out("data: %d is false \n", validPoint);
	validPoint = grid->nodePosValid(3, 2);
	Trace::out("data: %d is false \n", validPoint);
	validPoint = grid->nodePosValid(3, 1);
	Trace::out("data: %d is false \n", validPoint);

	grid->findShortestPath();
	grid->printNodePath();


}

// ---  End of File ---
