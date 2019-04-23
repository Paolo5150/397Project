#pragma once
#include "..\GameObject\GameObject.h"
#include <list>

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
	QuadNode *topLeft;
	QuadNode *bottomLeft;
	QuadNode *topRight;
	QuadNode *bottomRight;

	std::list<GameObject*> gameObjects;

	void Split();

};

class QuadTree
{
public:
	QuadTree(int centerX, int centerY, int sizeX, int sizeY);
	~QuadTree();

	QuadNode* root;

	void AddGameObject(GameObject* go, float posX, float posZ);
	int GameObjectInQuadrant(int x, int y);
	void ClearNodes();

private:
	void AddGameObject(GameObject* go, float posX, float posZ, QuadNode* &node);
	void ClearNode(QuadNode* &node);
	int GameObjectInQuadrant(int x, int y, QuadNode* node);
	void DeleteNode(QuadNode*& n);

};