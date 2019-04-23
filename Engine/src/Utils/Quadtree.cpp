#include "Quadtree.h"


QuadNode::QuadNode(int centerX, int centerY, int sizeX, int sizeY) : centerX(centerX), centerY(centerY), width(sizeX), height(sizeY)
{
	bottomRight = nullptr;
	bottomLeft = nullptr;
	topLeft = nullptr;
	topRight = nullptr;
	isSplit = 0;
}


void QuadNode::Split()
{
	isSplit = 1;

	Logger::LogError("Split, top left", centerX - width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, top right", centerX + width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom left", centerX - width / 4, centerY - height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom right", centerX + width / 4, centerY - height / 4, width / 2, height / 2);

	topLeft = new QuadNode(centerX - width / 4, centerY + height / 4, width / 2, height / 2);
	topRight = new QuadNode(centerX + width / 4, centerY + height / 4, width / 2, height / 2);
	bottomRight = new QuadNode(centerX + width / 4, centerY - height / 4, width / 2, height / 2);
	bottomLeft = new QuadNode(centerX - width / 4, centerY - height / 4, width / 2, height / 2);

}


QuadTree::QuadTree(int centerX, int centerY, int sizeX, int sizeY)
{
	root = new QuadNode(centerX, centerY, sizeX, sizeY);
	//Logger::LogError("Quadtree created", centerX,centerY,sizeX, sizeY);

	root->Split();
}

QuadTree::~QuadTree()
{
	DeleteNode(root);
}

void QuadTree::DeleteNode(QuadNode*& n)
{
	if (n->isSplit)
	{
		DeleteNode(n->topLeft);
		DeleteNode(n->topRight);
		DeleteNode(n->bottomLeft);
		DeleteNode(n->bottomRight);
	}
	else
		delete n;
}


void QuadTree::AddGameObject(GameObject* go, float posX, float posZ)
{
	AddGameObject(go, posX, posZ, root);
}

int QuadTree::GameObjectInQuadrant(int x, int y)
{
	return GameObjectInQuadrant(x, y, root);
}

int QuadTree::GameObjectInQuadrant(int x, int z, QuadNode* node)
{
	if (node->isSplit)
	{
		if (x <= node->centerX && z >= node->centerY)
			return GameObjectInQuadrant(x, z, node->topLeft);

		if (x <= node->centerX && z <= node->centerY)
			return GameObjectInQuadrant(x, z, node->bottomLeft);

		if (x >= node->centerX && z >= node->centerY)
			return GameObjectInQuadrant(x, z, node->topRight);

		if (x >= node->centerX && z <= node->centerY)
			return GameObjectInQuadrant(x, z, node->bottomRight);
	}
	else
		return node->gameObjects.size();
}

void QuadTree::AddGameObject(GameObject* go, float posX, float posZ, QuadNode* &node)
{
	if (node->isSplit)
	{
		//Logger::LogError("Added object at", posX, posZ);

	
		if (posX <= node->centerX && posZ >= node->centerY)
		{
			//Logger::LogError("Added top left");
			AddGameObject(go, posX, posZ, node->topLeft);
		}

		if (posX <= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom left");

			AddGameObject(go, posX, posZ, node->bottomLeft);
		}

		if (posX >= node->centerX && posZ >= node->centerY)
		{		
			//Logger::LogError("Added top right");

			AddGameObject(go, posX, posZ, node->topRight);
		}

		if (posX >= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom right");

			AddGameObject(go, posX, posZ, node->bottomRight);
		}
	}
	else
		node->gameObjects.push_back(go);
}

void QuadTree::ClearNodes()
{
	ClearNode(root);
}

void QuadTree::ClearNode(QuadNode* &node)
{
	node->gameObjects.clear();

	if (node->isSplit)
	{
		ClearNode(node->topLeft);
		ClearNode(node->topRight);
		ClearNode(node->bottomLeft);
		ClearNode(node->bottomRight);
	}
}

