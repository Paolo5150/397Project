#pragma once

#include "..\Components\PathNode.h"
#include "Quadtree.h"
#include <vector>

class Terrain;

/**
* @class PathFinder
* @brief Manages path finding on the terrain
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class PathFinder
{
public:
	/**
	* @brief						Return the PathFinder instance
	*
	* @pre							The PathFinder must exist
	* @post							The PathFinder instance is returned
	*/
	static PathFinder& Instance();

	/**
	* @brief						Generate the grapsh of nodes based on terrain size
	*
	* @pre							The PathFinder must exist
	* @post							The grapsh is created
	* @param terrain				The terrain
	*/
	void Generate(Terrain* terrain);

	/**
	* @brief						Destroy the instance and nodes
	*
	* @pre							The PathFinder must exist
	* @post							The PathFinder is destroyed
	*/
	~PathFinder();

	/**
	* @brief						Returns the closest node to the give position
	*
	* @pre							The PathFinder must exist
	* @post							The closest node to the give position is returned
	* @param x						The x position
	* @param y						The y position
	* @param z						The z position
	*/
	PathNode* ClosestNodeAt(int x, int y, int z);

	/**
	* @brief						Initialize the nodes
	*
	* @pre							The PathFinder must exist
	* @post							The nodes are initialized
	*/
	void Start();
	

	/**
	* @brief						Returns a node at random position with no obstacles in it
	*
	* @pre							The PathFinder must exist
	* @post							The nodes is returned
	* @return						The node at random position with no obstacles in it
	*/
	glm::vec3 GetRandomFreeNodePosition();

	/**
	* @brief						Returns the first 2 nodes between start position and destination
	*
	* @pre							The PathFinder must exist
	* @post							The nodes are returned
	* @return						The first 2 nodes between start position and destination
	* @param start					The starting position in world space
	* @param finish					The destination position in world space
	*/
	std::vector<glm::vec3> GeneratePath(glm::vec3 start, glm::vec3 finish);

	void DeleteNodes();

	/**
	* @brief						List of nodes in no particular order
	*/
	std::vector<PathNode*> pathNodes;
private:
	/**
	* @brief						Create PathFinder object
	*/
	PathFinder();
	/**
	* @brief						Quadtree of nodes
	*/
	QuadTree<PathNode*>* nodesQT;

	/**
	* @brief						The 2D map of nodes
	*/
	std::vector<std::vector<PathNode*>> nodeMap;
};