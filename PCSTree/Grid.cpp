//-----------------------------------------------------------------------------
// Copyright 2024, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Grid.h"
#include "Node.h"

using namespace std;
namespace Azul
{
	//Grid::Grid() {}
	//Grid::~Grid() {}

	//bool Grid::checkIfNodeVisited() {}
	//Grid::Grid(Grid* _startNode, Grid* _endNode)
	//{
	//	this->startNode = _startNode;
	//	this->endNode = _endNode;
	//}

	void Grid::createGridManual()
	{
		this->gridWidth_x = 3;
		this->gridHeight_y = 3;
		
		// create 6 nodes
		// A = 0,0
		Node* nodeA = new Node(0, 0, "nodeA", nullptr, nullptr, nullptr, nullptr);
		this->pHead = nodeA;

		// B = 1,0
		Node* nodeB = new Node(1, 0, "nodeB", nullptr, nullptr, nullptr, nullptr);

		// C = 0,1
		Node* nodeC = new Node(0, 1, "nodeC", nullptr, nullptr, nullptr, nullptr);

		// E = 1,1
		Node* nodeE = new Node(1, 1, "nodeE", nullptr, nullptr, nullptr, nullptr);

		// D = 2,0
		Node* nodeD = new Node(2, 0, "nodeD", nullptr, nullptr, nullptr, nullptr);

		// G = 2,1
		Node* nodeG = new Node(2, 1, "nodeG", nullptr, nullptr, nullptr, nullptr);

		// F = 0,2
		Node* nodeF = new Node(0, 2, "nodeF", nullptr, nullptr, nullptr, nullptr);

		// H = 1,2
		Node* nodeH = new Node(1, 2, "nodeH", nullptr, nullptr, nullptr, nullptr);

		// I = 2,2
		Node* nodeI = new Node(2, 2, "nodeI", nullptr, nullptr, nullptr, nullptr);

		// connect it all
		// if no connection, then nullptr
		// connect A to B,C
		nodeA->connectNode(nodeC, nullptr, nodeB, nullptr);
		// connect B to A,E,D
		nodeB->connectNode(nodeE, nullptr, nodeD, nodeA);
		// connect C to A,E
		nodeC->connectNode(nodeF, nodeA, nodeE, nullptr);
		// connect E to B,C,G
		nodeE->connectNode(nodeH, nodeB, nodeG, nodeC);
		// connect D to G,E,B
		nodeD->connectNode(nodeG, nullptr, nullptr, nodeB);
		// connect G to E,B,D
		nodeG->connectNode(nodeI, nodeD, nullptr, nodeE);
		// connect F to E,B,D
		nodeF->connectNode(nullptr, nodeC, nodeH, nullptr);
		// connect H to E,B,D
		nodeH->connectNode(nullptr, nodeE, nodeI, nodeF);
		// connect I to E,B,D
		nodeI->connectNode(nullptr, nodeG, nullptr, nodeH);

		// hard code blocked nodes
		nodeC->isNodeBlocked = true;
		nodeE->isNodeBlocked = true;

	}

	/*void Grid::createGrid(int _gridWidth_x, int _gridHeight_y)
	{
		this->gridWidth_x = _gridWidth_x;
		this->gridHeight_y = _gridHeight_y;
		list<Node*> nodeList;
		string name;

		for (int i = 0; i < this->gridWidth_x; i++)
		{
			for (int j = 0; j < this->gridHeight_y; j++)
			{
				name = to_string(i) + "_" + to_string(j);
				Node* const node = new Node(i, j, name, nullptr, nullptr, nullptr, nullptr);
				nodeList.push_back(node);
			}
		}

		for (const Node* node : nodeList)
		{
			node->pLeftNode = 
			node->pUpNode = 
			node->pRightNode = 
			node->pDownNode = 

		}


	}*/
	
	bool Grid::setStartNode_pos(int x, int y)
	{
		bool validPoint = nodePosValid(x, y);
		if (validPoint)
		{
			this->startNode = getNodeFromPos(x, y);
			// initialize startNode only once at the beginning of the algorithm
			assert(endNode != nullptr);
			startNode->globalGoal = calcNodeDistance(startNode, endNode);
			startNode->localGoal = 0;
		}
		
		return validPoint;
	}

	bool Grid::setEndNode_pos(int x, int y)
	{
		bool validPoint = nodePosValid(x, y);
		if (validPoint)
		{
			this->endNode = getNodeFromPos(x, y);
		}

		return validPoint;
	}

	bool Grid::nodePosValid(int x, int y)
	{
		// x,y not equal to grid width or grid height because nodes start at 0,0 not at 1,1
		if (x < gridWidth_x && y < gridHeight_y)
		{
			return true;
		}
		else
		{
			return false;
		}
	
	}

	float Grid::calcNodeDistance(Node* start, Node* end)
	{
		float x_d = float(end->x_pos - start->x_pos);
		float y_d = float(end->y_pos - start->y_pos);
		
		float dist = sqrtf((x_d * x_d) + (y_d * y_d));

		return dist;
	}
	Node* Grid::getNodeFromPos(int x, int y)
	{
		Node* pneighNode = pHead;

		// do stuff
		//pneighNode->pRightNode*i
		int i;
		for (i = 0; i < x; i++)
		{
			pneighNode = pneighNode->pRightNode;
		}
		for (i = 0;i < y; i++)
		{
			pneighNode = pneighNode->pUpNode;
		}

		return pneighNode;
	}

	Node* Grid::findBestNeighbor(Node* primeNode)
	{
		primeNode->isNodeVisited = true; 
		
		Node* neighborNodes[] = { primeNode->pUpNode, primeNode->pDownNode, primeNode->pRightNode, primeNode->pLeftNode };
		Node* bestNode = nullptr;
		Node* neighNode;
		// keep visied node in a separate list
		this->visitedNodeList.push_back(primeNode);
		float localGoalofNeigNode = 0.0f;

		for (int i = 0;i < 4; i++)
		{
			neighNode = neighborNodes[i];
			if (neighNode != nullptr && !neighNode->isNodeVisited && !neighNode->isNodeBlocked)
			{
				localGoalofNeigNode = primeNode->localGoal + calcNodeDistance(primeNode, neighNode);
				// First check if local goal of neigbor node is greater than [localGoal of primeNode + distance b/w prime and neig node]
				if (neighNode->localGoal > localGoalofNeigNode)
				{
					neighNode->localGoal = localGoalofNeigNode;
					neighNode->globalGoal = neighNode->localGoal + calcNodeDistance(neighNode, this->endNode);
				}
				// sort nodeList in ascending order of global goal
				if (bestNode == nullptr || neighNode->globalGoal > bestNode->globalGoal)
				{
					bestNode = neighNode;
				}
			}
		}

		assert(bestNode != nullptr);
		return bestNode;
	}

	void Grid::findShortestPath()
	{
		//start w/ startnode 
		Node* currNode = this->startNode;
		Node* bestNode;

		// loop through path findBestNeighbor()
		while (currNode!=this->endNode)
		{
			bestNode = findBestNeighbor(currNode);
			currNode = bestNode;
		}
	}
	
	void Grid::printNodePath() const
	{
		for (const Node* node : visitedNodeList)
		{
			Trace::out("node: %s \n",(node->nodeName).c_str());
		}
		Trace::out("node: %s \n", (this->endNode->nodeName).c_str());
	}
}

// ---  End of File ---
