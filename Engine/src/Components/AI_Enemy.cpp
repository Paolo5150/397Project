#include "AI_Enemy.h"

AI_Enemy::AI_Enemy(AIState state) : Component("AI_Enemy")
{
	_type = "AI";
	_parentTransform = GetParent()->transform;
	SetState(state);
	_moveDir = RandUtils::RandFloat(0, 360);
}


AI_Enemy::~AI_Enemy()
{

}

void AI_Enemy::SetState(AIState state)
{
	_state = state;
}

AIState AI_Enemy::GetState() const
{
	return _state;
}

void AI_Enemy::Update()
{
	Think();
}

void AI_Enemy::Think()
{
	switch (_state)
	{
		case AIState::Wander:
			Wander();
			break;
		case AIState::Seek:
			Seek();
			break;
		case AIState::Fight:
			Fight();
			break;
		case AIState::Flee:
			Flee();
			break;
		default:
			throw "Invalid_AI_State";
			break;
	}
}

void AI_Enemy::Wander()
{
	_moveDir += RandUtils::RandFloat(-2, 2);
	_parentTransform.SetPosition(_parentTransform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * _parentTransform.GetLocalFront()));
}

void AI_Enemy::Seek()
{

}

void AI_Enemy::Fight()
{

}

void AI_Enemy::Flee()
{

}