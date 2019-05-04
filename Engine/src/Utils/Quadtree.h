#pragma once
#include "..\GameObject\GameObject.h"
#include <list>
#include <set>

template <class T>
class NodeElement
{
public:
	NodeElement(T& telement, int x, int z, int sx, int sz) : element(telement), posX(x), posZ(z), sizeX(sx), sizeZ(sz){}
	NodeElement(T& telement, int x, int z) : element(telement), posX(x), posZ(z){}

	T& element;
	int posX;
	int posZ;
	int sizeX;
	int sizeZ;
	int maxElementInNode;
};

template <class T>
class QuadNode
{
public:
	QuadNode(int centerX, int centerY, int sizeX, int sizeY, int maxElementsInNode);
	~QuadNode(){};

	int width;
	int height;

	int centerX;
	int centerY;
	int maxElements;
	bool isSplit;
	QuadNode<T> *topLeft;
	QuadNode<T> *bottomLeft;
	QuadNode<T> *topRight;
	QuadNode<T> *bottomRight;

	std::set<T> elements;

	void Split();

};

template <class T>
class QuadTree
{
public:
	QuadTree(int centerX, int centerY, int sizeX, int sizeY, int maxElements = 10000);
	~QuadTree();

	QuadNode<T>* root;

	void AddElement(T go, float posX, float posZ);
	void AddElement(T go, float posX, float posZ, float sizeX, float sizeZ);
	int GameObjectInQuadrant(int x, int y);
	void ClearNodes();
	std::set<T>& GameObjectsAt(int x, int y);

private:
	void AddElement(NodeElement<T> go, float posX, float posZ, QuadNode<T>* &node);
	void AddElement(NodeElement<T> go, float posX, float posZ, float sizeX, float sizeZ, QuadNode<T>* &node);
	void ClearNode(QuadNode<T>* &node);
	int GameObjectInQuadrant(int x, int y, QuadNode<T>* node);
	std::set<T>& GameObjectsAt(int x, int y, QuadNode<T>* node);

	void DeleteNode(QuadNode<T>*& n);

};

template <class T>
QuadNode<T>::QuadNode(int centerX, int centerY, int sizeX, int sizeY, int maxElements) : centerX(centerX), centerY(centerY), width(sizeX), height(sizeY)
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

	topLeft = new QuadNode<T>(centerX - width / 4, centerY + height / 4, width / 2, height / 2,maxElements);
	topRight = new QuadNode<T>(centerX + width / 4, centerY + height / 4, width / 2, height / 2, maxElements);
	bottomRight = new QuadNode<T>(centerX + width / 4, centerY - height / 4, width / 2, height / 2, maxElements);
	bottomLeft = new QuadNode<T>(centerX - width / 4, centerY - height / 4, width / 2, height / 2, maxElements);

}

template <class T>
QuadTree<T>::QuadTree(int centerX, int centerY, int sizeX, int sizeY, int maxElements)
{
	root = new QuadNode<T>(centerX, centerY, sizeX, sizeY,maxElements);
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
	NodeElement<T> element(go,posX,posZ);

	AddElement(element, posX, posZ, root);
}

template <class T>
void QuadTree<T>::AddElement(T go, float posX, float posZ, float sizeX, float sizeZ)
{
	NodeElement<T> element(go, posX, posZ,sizeX, sizeZ);

	AddElement(element, posX, posZ, sizeX, sizeZ, root);
}

template <class T>
int QuadTree<T>::GameObjectInQuadrant(int x, int y)
{
	return GameObjectInQuadrant(x, y, root);
}

template <class T>
std::set<T>& QuadTree<T>::GameObjectsAt(int x, int y)
{
	return GameObjectsAt(x, y, root);
}

template <class T>
std::set<T>& QuadTree<T>::GameObjectsAt(int x, int z, QuadNode<T>* node)
{
	if (node->isSplit)
	{
		if (x <= node->centerX && z >= node->centerY)
			return GameObjectsAt(x, z, node->topLeft);

		if (x <= node->centerX && z <= node->centerY)
			return GameObjectsAt(x, z, node->bottomLeft);

		if (x >= node->centerX && z >= node->centerY)
			return GameObjectsAt(x, z, node->topRight);

		if (x >= node->centerX && z <= node->centerY)
			return GameObjectsAt(x, z, node->bottomRight);
	}
	else
		return node->elements;
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
		return node->elements.size();
}

template <class T>
void QuadTree<T>::AddElement(NodeElement<T> go, float posX, float posZ, QuadNode<T>* &node)
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
	{
		node->elements.insert(go.element);
	}
}


template <class T>
void QuadTree<T>::AddElement(NodeElement<T> go, float posX, float posZ, float sizeX, float sizeZ, QuadNode<T>* &node)
{
	if (node->isSplit)
	{
		//Logger::LogError("Added object at", posX, posZ);

		if (posX - sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX - sizeX / 2 >= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX - sizeX / 2 >= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX - sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX + sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX + sizeX / 2 >= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX + sizeX / 2 >= node->centerX && posZ - sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX + sizeX / 2 <= node->centerX && posZ - sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX - sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX - sizeX / 2 >= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX - sizeX / 2 >= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX - sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);

		/**/
		if (posX + sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topLeft);

		else if (posX + sizeX / 2 >= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->topRight);

		if (posX + sizeX / 2 >= node->centerX && posZ + sizeZ / 2 <= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomRight);

		else if (posX + sizeX / 2 <= node->centerX && posZ + sizeZ / 2 >= node->centerY)
			AddElement(go, posX, posZ, sizeX, sizeZ, node->bottomLeft);



	}
	else
		node->elements.insert(go.element);
}


template <class T>
void QuadTree<T>::ClearNodes()
{
	ClearNode(root);
}

template <class T>
void QuadTree<T>::ClearNode(QuadNode<T>* &node)
{
	node->elements.clear();

	if (node->isSplit)
	{
		ClearNode(node->topLeft);
		ClearNode(node->topRight);
		ClearNode(node->bottomLeft);
		ClearNode(node->bottomRight);
	}
}

