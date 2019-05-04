#include "AIBase.h"

AIBase::AIBase(std::string scriptPath, AIState state) : Component("AIBase")
{
	_type = "AI";
	_state = "";
	_luaState = NULL;
	_lastStateChange = 0.0f;
	_wanderDirection = 0.0f;
	_randomTimer = 0.0f;
	_scriptPath = scriptPath;
}

AIBase::AIBase(Transform& targetTransform, std::string scriptPath, AIState state) : Component("AIBase")
{
	_type = "AI";
	_state = "";
	_luaState = NULL;
	_lastStateChange = 0.0f;
	_wanderDirection = 0.0f;
	_randomTimer = 0.0f;
	SetTarget(targetTransform);
	_scriptPath = scriptPath;
}

AIBase::~AIBase()
{
}

void AIBase::SetTarget(Transform& targetTransform)
{
	_targetTransform = &targetTransform;
}

float AIBase::GetDistanceToTarget() const
{
	return sqrt(pow(_targetTransform->GetPosition().x - _parentTransform->GetPosition().x, 2) + pow(_targetTransform->GetPosition().y - _parentTransform->GetPosition().y, 2) + pow(_targetTransform->GetPosition().z - _parentTransform->GetPosition().z, 2));
}

float AIBase::GetRotationToTarget() const
{
	glm::vec3 toTarget = glm::vec3(_targetTransform->GetPosition().x, _parentTransform->GetPosition().y, _targetTransform->GetPosition().z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

float AIBase::GetReverseRotationToTarget() const
{
	glm::vec3 toTarget = glm::vec3(_targetTransform->GetPosition().x, _parentTransform->GetPosition().y, _targetTransform->GetPosition().z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget))) - 180;
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

Transform* AIBase::GetTarget() const
{
	return _targetTransform;
}

void AIBase::SetState(std::string state)
{
	_state = state;
	_lastStateChange = Timer::GetTimeS();
}

std::string AIBase::GetState() const
{
	return _state;
}

void AIBase::Move(float forward, float right)
{
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (forward * _parentTransform->GetLocalFront()));
	_parentTransform->SetPosition(_parentTransform->GetPosition() + (right * _parentTransform->GetLocalRight()));
}

void AIBase::Rotate(float amount)
{
	_parentTransform->RotateBy(amount, 0, 1, 0);
}

void AIBase::SetAnimation(int index)
{
	GetParent()->GetComponent<Animator>("Animator")->SetCurrentAnimation(index);
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
	Lua::InitLua(_luaState);
	Lua::ExecuteLuaScript(_luaState, _scriptPath);

	lua_settop(_luaState, 0);
	lua_getglobal(_luaState, "Think");
	lua_pushstring(_luaState, GetState().c_str());
	lua_pushnumber(_luaState, GetDistanceToTarget());
	lua_pushnumber(_luaState, GetRotationToTarget());
	lua_pushnumber(_luaState, GetReverseRotationToTarget());
	lua_pushnumber(_luaState, Timer::GetTimeS());
	lua_pushnumber(_luaState, Timer::GetDeltaS());
	lua_pushnumber(_luaState, _lastStateChange);
	lua_pushnumber(_luaState, _randomTimer);

	lua_call(_luaState, 8, 6); //call the function with 7 arguments and return 6 results

	if (Lua::GetStringFromStack("_state", _luaState) != GetState())
	{
		SetState(Lua::GetStringFromStack("_state", _luaState));
	}
	Rotate(Lua::GetFloatFromStack("rotation", _luaState));
	Move(Lua::GetFloatFromStack("fowardMovement", _luaState), Lua::GetFloatFromStack("rightMovement", _luaState));
	SetAnimation(Lua::GetIntFromStack("animation", _luaState));
	_wanderDirection = Lua::GetFloatFromStack("_wanderDirection", _luaState);

	Lua::CloseLua(_luaState);
}