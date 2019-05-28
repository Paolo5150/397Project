#pragma once

#include "..\GameObject\GameObject.h"
#include "BoxCollider.h"
#include <vector>

/**
* @class PathNode
* @brief Class defining a node used for pathfinding
*
*
* @author Paolo Ferri
* @version 01
* @date 16/05/2019
* @bug No known bugs.
*/
class PathNode : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The PathNode does not exist
	* @post			The PathNode is created
	*/
	PathNode();

	/**
	* @brief		Destructor
	* @pre			The PathNode must exist
	* @post			The PathNode is destroyed
	*/
	~PathNode();

	/**
	* @brief		Callback invoked when collision occurs
	* @pre			The PathNode must exist
	* @param go		The game object collided against
	*/
	void OnCollision(GameObject* go) override;

	/**
	* @brief		Initialize node
	* @pre			The PathNode must exist
	*/
	void Start() override;

	/**
	* @brief		Overridable method for update
	* @pre			The PathNode must exist
	*/
	void Update() override;

	/**
	* @brief		Overridable method for engine update
	* @pre			The PathNode must exist
	*/
	void EngineUpdate() override;

	/**
	* @brief		Overridable method for late update
	* @pre			The PathNode must exist
	*/
	void LateUpdate() override;

	/**
	* @brief		The node collider
	*/
	BoxCollider* sc;

	/**
	* @brief		The list of nodes neighbors
	*/
	std::vector<PathNode*> neighbors;

	/**
	* @brief		The distance from the previous closest node
	*/
	double distanceFromPrevious;

	/**
	* @brief		The distance from the destination
	*/
	double distanceFromTarget;

	/**
	* @brief		The traversal cost of the noden
	*/
	double cost;

	/**
	* @brief		Whether the node has been checked
	*/
	bool checked;
};