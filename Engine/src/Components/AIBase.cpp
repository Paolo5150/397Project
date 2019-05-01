#include "AIBase.h"

AIBase::AIBase(AIState state) : Component("AIBase")
{
	_type = "AI";
	SetState(state);
	_targetDirection = RandUtils::RandFloat(0, 360);
	_movementSpeed = 50.0f;
}

AIBase::AIBase(Transform targetTransform, AIState state) : Component("AIBase")
{
	_type = "AI";
	SetState(state);
	_targetDirection = RandUtils::RandFloat(0, 360);
	_movementSpeed = 50.0f;
	_targetTransform = &targetTransform;
}

AIBase::~AIBase()
{

}

void AIBase::SetTarget(Transform targetTransform)
{
	_targetTransform = &targetTransform;
}

float AIBase::GetDistanceToTarget()
{
	return sqrt(pow(_targetTransform->GetPosition().x - _parentTransform->GetPosition().x, 2) + pow(_targetTransform->GetPosition().y - _parentTransform->GetPosition().y, 2) + pow(_targetTransform->GetPosition().z - _parentTransform->GetPosition().z, 2));
}

float AIBase::GetBearingToTarget()
{
	Transform* toCam = glm::dot(_parentTransform, _targetTransform);
}

Transform* AIBase::GetTarget()
{
	return _targetTransform;
}

void AIBase::SetState(AIState state)
{
	_state = state;
	_lastStateChange = Timer::GetTimeS();
}

AIState AIBase::GetState() const
{
	return _state;
}

void AIBase::SetMovementSpeed(float movementSpeed)
{
	if (movementSpeed >= 0)
	{
		_movementSpeed = movementSpeed;
	}
}

float AIBase::GetMovementSpeed() const
{
	return _movementSpeed;
}

void AIBase::SetRotationSpeed(float rotationSpeed)
{
	if (rotationSpeed >= 0)
	{
		_rotationSpeed = rotationSpeed;
	}
}

float AIBase::GetRotationSpeed() const
{
	return _rotationSpeed;
}

void AIBase::SetFleeDistance(float fleeDistance)
{
	_fle
}

float AIBase::GetFleeDistance()
{

}

void AIBase::SetAgroDistance(float agroDistance)
{

}

float AIBase::GetAgroDistance()
{

}

void AIBase::SetMaxFollowDistance(float maxFollowDistance)
{

}

float AIBase::GetMaxFollowDistance()
{

}

void AIBase::Update()
{
	Logger::LogInfo(GetBearingToTarget());

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
		case AIState::Idle:
			Idle();
			break;
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

void AIBase::Idle()
{
	if (RandUtils::RandInt(1, 100) < 10 && Timer::GetTimeS() - _lastStateChange > 5.0f)
	{
		SetState(AIState::Wander);
	}

	if (GetDistanceToTarget() < 100.0f)
	{
		SetState(AIState::Seek);
	}
}

void AIBase::Wander()
{
	if (RandUtils::RandInt(1, 100) <= 10)
	{
		_targetDirection += RandUtils::RandFloat(-10, 0);
	}
	else if (RandUtils::RandInt(1, 100) >= 90)
	{
		_targetDirection += RandUtils::RandFloat(-0, 10);
	}

	/*if (_parentTransform->GetLocalFront() < _targetDirection)
	{
		_parentTransform->RotateBy(_targetDirection, glm::vec3(0, 1, 0));
		_parentTransform->SetPosition(_parentTransform->GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * _parentTransform->GetLocalFront()));
	}*/

	if (RandUtils::RandInt(1, 100) < 10 && Timer::GetTimeS() - _lastStateChange > 5.0f)
	{
		SetState(AIState::Idle);
	}

	if (GetDistanceToTarget() < 100.0f)
	{
		SetState(AIState::Seek);
	}
}

void AIBase::Seek()
{
	if (GetDistanceToTarget() > 150.0f)
	{
		SetState(AIState::Wander);
	}
}

void AIBase::Fight()
{
	//Attack the target here
}

void AIBase::Flee()
{
	//Pick the opposite direction to the target and run until you are x distance away
}