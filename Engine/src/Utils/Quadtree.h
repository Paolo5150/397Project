#pragma once
#include "..\GameObject\GameObject.h"
#include <list>

template <class T>
class QuadNode
{
public:
	QuadNode(int centerX, int centerY, int sizeX, int sizeY);
	~QuadNode(){};

	int width;
	int height;

	int centerX;
	int centerY;

	bool isSplit;
	QuadNode<T> *topLeft;
	QuadNode<T> *bottomLeft;
	QuadNode<T> *topRight;
	QuadNode<T> *bottomRight;

	std::list<T> gameObjects;

	void Split();

};

template <class T>
class QuadTree
{
public:
	QuadTree(int centerX, int centerY, int sizeX, int sizeY);
	~QuadTree();

	QuadNode<T>* root;

	void AddElement(T go, float posX, float posZ);
	int GameObjectInQuadrant(int x, int y);
	void ClearNodes();

private:
	void AddElement(T go, float posX, float posZ, QuadNode<T>* &node);
	void ClearNode(QuadNode<T>* &node);
	int GameObjectInQuadrant(int x, int y, QuadNode<T>* node);
	void DeleteNode(QuadNode<T>*& n);

};

template <class T>
QuadNode<T>::QuadNode(int centerX, int centerY, int sizeX, int sizeY) : centerX(centerX), centerY(centerY), width(sizeX), height(sizeY)
{
	bottomRight = nullptr;
	bottomLeft = nullptr;
	topLeft = nullptr;
	topRight = nullptr;
	isSplit = 0;
}

template <class T>
void QuadNode<T>::Split()
{
	isSplit = 1;

	Logger::LogError("Split, top left", centerX - width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, top right", centerX + width / 4, centerY + height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom left", centerX - width / 4, centerY - height / 4, width / 2, height / 2);
	Logger::LogError("Split, bottom right", centerX + width / 4, centerY - height / 4, width / 2, height / 2);

	topLeft = new QuadNode<T>(centerX - width / 4, centerY + height / 4, width / 2, height / 2);
	topRight = new QuadNode<T>(centerX + width / 4, centerY + height / 4, width / 2, height / 2);
	bottomRight = new QuadNode<T>(centerX + width / 4, centerY - height / 4, width / 2, height / 2);
	bottomLeft = new QuadNode<T>(centerX - width / 4, centerY - height / 4, width / 2, height / 2);

}

template <class T>
QuadTree<T>::QuadTree(int centerX, int centerY, int sizeX, int sizeY)
{
	root = new QuadNode<T>(centerX, centerY, sizeX, sizeY);
	//Logger::LogError("Quadtree created", centerX,centerY,sizeX, sizeY);

	root->Split();
}

template <class T>
QuadTree<T>::~QuadTree()
{
	DeleteNode(root);
}

template <class T>
void QuadTree<T>::DeleteNode(QuadNode<T>*& n)
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

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ)
{
	AddElement(go, posX, posZ, root);
}

template <class T>
int QuadTree<T>::GameObjectInQuadrant(int x, int y)
{
	return GameObjectInQuadrant(x, y, root);
}

template <class T>
int QuadTree<T>::GameObjectInQuadrant(int x, int z, QuadNode<T>* node)
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

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ, QuadNode<T>* &node)
{
	if (node->isSplit)
	{
		//Logger::LogError("Added object at", posX, posZ);


		if (posX <= node->centerX && posZ >= node->centerY)
		{
			//Logger::LogError("Added top left");
			AddElement(go, posX, posZ, node->topLeft);
		}

		if (posX <= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom left");

			AddElement(go, posX, posZ, node->bottomLeft);
		}

		if (posX >= node->centerX && posZ >= node->centerY)
		{
			//Logger::LogError("Added top right");

			AddElement(go, posX, posZ, node->topRight);
		}

		if (posX >= node->centerX && posZ <= node->centerY)
		{
			//Logger::LogError("Added bottom right");

			AddElement(go, posX, posZ, node->bottomRight);
		}
	}
	else
		node->gameObjects.push_back(go);
}

template <class T>
void QuadTree<T>::ClearNodes()
{
	ClearNode(root);
}

template <class T>
void QuadTree<T>::ClearNode(QuadNode<T>* &node)
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

