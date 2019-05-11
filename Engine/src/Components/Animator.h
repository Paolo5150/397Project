#pragma once
#include "..\Graphics\AnimatedModel.h"
#include "..\Graphics\ModelAnimation.h"
#include "..\GameObject\Component.h"
#include <set>


class Animator : public Component
{

public:
	friend class Model;
	friend class AnimatedModel;


	Animator(AnimatedModel* m);
	~Animator();

	void SetAnimationSpeed(float speed) { animationSpeed = speed; }
	void SetCurrentAnimation(int animation, bool loop = true);
	void Reset();
	void OnPreRender(Camera& cam, Shader* currentShader = nullptr);

private:
	float animationSpeed;
	bool isPlaying;
	bool isResetting;

	std::vector<ModelAnimation> animations;
	std::set<Shader*> shaderToUpdate;

	void EngineUpdate() override;

	void Update() override;
	ModelAnimation* currentAnimation;
	int currentAnimationIndex;
	AnimatedModel* model;
	std::vector<glm::mat4> allBonesTransforms;
	double time_in_ticks;
	float animation_time;
	float previos_animation_Time;
	bool playedOnce;

};

