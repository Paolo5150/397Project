#include "AIBase.h"

AIBase::AIBase(AIState state) : Component("AIBase")
{
	_type = "AI";
	SetState(state);
	_moveDir = RandUtils::RandFloat(0, 360);
	_moveSpeed = 50.0f;
}

AIBase::~AIBase()
{

}

void AIBase::SetState(AIState state)
{
	_state = state;
}

void AIBase::SetMoveSpeed(float moveSpeed)
{
	if (moveSpeed >= 0)
	{
		_moveSpeed = moveSpeed;
	}
}

AIState AIBase::GetState() const
{
	return _state;
}

float AIBase::GetMoveSpeed() const
{
	return _moveSpeed;
}

void AIBase::Update()
{
	Think();
}

void AIBase::OnAttach(GameObject* go)
{
	_parentTransform = &go->transform;
}

void AIBase::Think()
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

void AIBase::Wander()
{
	if (RandUtils::RandInt(1, 100) <= 10)
	{
		_moveDir = RandUtils::RandFloat(-10, 0);
	}
	else if (RandUtils::RandInt(1, 100) >= 90)
	{
		_moveDir = RandUtils::RandFloat(-0, 10);
	}
	else
	{
		_moveDir = 0.0f;
	}

	if (RandUtils::RandInt(1, 100) < 90)
	{
		_parentTransform->RotateBy(_moveDir, glm::vec3(0, 1, 0));
		_parentTransform->SetPosition(_parentTransform->GetPosition() + (GetMoveSpeed() * Timer::GetDeltaS() * _parentTransform->GetLocalFront()));
	}
}

void AIBase::Seek()
{

}

void AIBase::Fight()
{

}

void AIBase::Flee()
{

}