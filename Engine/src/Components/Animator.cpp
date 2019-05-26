#include "Animator.h"
#include "..\Core\Timer.h"



Animator::Animator(AnimatedModel* m) : Component("Animator")
{
	model = m;


	for (unsigned int i = 0; i < m->allAnimations.size(); i++)
		animations.push_back(m->allAnimations[i]);

	currentAnimationIndex = 0;
	currentAnimation = &animations[currentAnimationIndex];
	allBonesTransforms.resize(model->GetTotalBones());

	isPlaying = true;
	animationSpeed = 1.0f;
	playedOnce = false;

	currentAnimation->loop = true;
	isResetting = 0;
	stopPercentage = 1.0;
}

Animator::~Animator()
{
	currentAnimation = NULL;
	model = NULL;
	animation_time = 0;
	previos_animation_Time = 0;

}

void Animator::Reset()
{
	animation_time = 0;
	isResetting = 0;
	previos_animation_Time = 0;
	time_in_ticks = 0;

}

void Animator::EngineUpdate()
{

}

void Animator::Update()
{

	
	if (animation_time < previos_animation_Time)
	{
		playedOnce = true;
	}
	previos_animation_Time = animation_time;

	//If animations is not in loop mode and already played once, reset to 0
	if (!currentAnimation->loop && playedOnce)
	{
		Reset();
	}

	if (isPlaying)
	{

		model->GetTransformations(animation_time, currentAnimation, allBonesTransforms);
	}
	else
		model->GetTransformations(0, currentAnimation, allBonesTransforms);

		time_in_ticks += Timer::GetDeltaS() * currentAnimation->ticksPerSecond;

		if (animation_time / currentAnimation->GetDuration() < stopPercentage)
			animation_time = fmod(time_in_ticks * animationSpeed, currentAnimation->GetDuration());

	

}
void Animator::OnPreRender(Camera& cam, Shader* currentShader)
{
	int loc = glGetUniformLocation(currentShader->GetID(), "bones");
	glUniformMatrix4fv(loc, allBonesTransforms.size(), GL_FALSE, (const GLfloat*)&allBonesTransforms[0]);
	/*auto it = shaderToUpdate.begin();
	//Update shader
	for (; it != shaderToUpdate.end() ; it++)
	{
	(*it)->Bind();

	int loc = glGetUniformLocation((*it)->GetID(), "bones");
	glUniformMatrix4fv(loc, allBonesTransforms.size(), GL_FALSE, (const GLfloat*)&allBonesTransforms[0]);

	}*/
	//glUseProgram(0);
}



void Animator::SetCurrentAnimation(int animation, bool loop)
{
	if (currentAnimationIndex == animation) return;

	if (animation >= animations.size())
		animation = animations.size() - 1;

	currentAnimation = &animations[animation];
	currentAnimationIndex = animation;
	if (loop == false)
	{
		currentAnimation->loop = false;
	}

	playedOnce = false;
	Reset();

}