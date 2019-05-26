#pragma once
#include "..\Graphics\AnimatedModel.h"
#include "..\Graphics\ModelAnimation.h"
#include "..\GameObject\Component.h"
#include <set>

/**
* @class Animator
* @brief Specialized class for animator component
*
* Manages animations for an animated model
*
* @author Paolo Ferri
* @version 01
* @date 1/05/2019
* @bug No known bugs.
*/
class Animator : public Component
{

public:
	friend class Model;
	friend class AnimatedModel;

	/**
	* @brief		Constructor
	* @pre			The animator does not exist
	* @post			The animator is created
	* @param m		The animated model
	*/
	Animator(AnimatedModel* m);


	/**
	* @brief		Destructor
	* @pre			The animator must exist
	* @post			The animator is destroyed
	*/
	~Animator();

	/**
	* @brief		Set the animation speed
	* @pre			The animator must exist
	* @post			The animation speed is updated
	* @param speed  The new animation speed
	*/
	void SetAnimationSpeed(float speed) { animationSpeed = speed; }

	/**
	* @brief		Set the animation index
	* @pre			The animator must exist
	* @post			The animation is updated
	* @param animation  The new animation index
	* @param look		Whether the animation should loop
	*/
	void SetCurrentAnimation(int animation, bool loop = true);

	/**
	* @brief		Restart the animation
	* @pre			The animator must exist
	* @post			The animation is restarted
	*/
	void Reset();

	/**
	* @brief		Callback invoked before rendering 
	* @pre			The animator must exist
	* @param cam	The camera used for rendering
	* @param currentShader The current active shader
	*/
	void OnPreRender(Camera& cam, Shader* currentShader = nullptr);

private:
	/**
	* @brief		The current animation speed
	*/
	float animationSpeed;

	/**
	* @brief		Whether the animaition is playing
	*/
	bool isPlaying;

	/**
	* @brief		Whether the animations has been reset
	*/
	bool isResetting;

	/**
	* @brief		Animations list
	*/
	std::vector<ModelAnimation> animations;

	/**
	* @brief		Overridden method for engine update
	*/
	void EngineUpdate() override;

	/**
	* @brief		Overridden method for update
	*/
	void Update() override;


	/**
	* @brief		The current animation
	*/
	ModelAnimation* currentAnimation;

	/**
	* @brief		Current animation index
	*/
	int currentAnimationIndex;

	/**
	* @brief		The model being animated
	*/
	AnimatedModel* model;

	/**
	* @brief		The bones transformation matrices
	*/
	std::vector<glm::mat4> allBonesTransforms;

	/**
	* @brief		Animation time track
	*/
	double time_in_ticks;

	/**
	* @brief		The animation time legnth
	*/
	float animation_time;

	/**
	* @brief		Previous animation time tick
	*/
	float previos_animation_Time;

	/**
	* @brief		Whether the animation has been played at leasts one time
	*/
	bool playedOnce;

};

