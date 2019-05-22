#include "AIBase.h"
#include <thread>
#include <future>

AIBase::AIBase(std::string scriptPath) : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_parentTransform = nullptr;
	_targetTransform = nullptr;
	_luaState = NULL;
	_otherTarget.x = -1;
	_otherTarget.y = -1;
	_otherTarget.z = -1;
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_scriptPath = scriptPath;
	_lastStateChange = 0.0f;
	_randomTimer = 0.0f;
	_updateTimer = 0.0f;
}

AIBase::AIBase(Transform& targetTransform, std::string scriptPath) : Component("AIBase")
{
	_type = "AI";
	SetState("");
	_luaState = NULL;
	_parentTransform = nullptr;
	SetTarget(targetTransform);
	_otherTarget.x = -1;
	_otherTarget.y = -1;
	_otherTarget.z = -1;
	_nextNode.x = -1;
	_nextNode.y = -1;
	_nextNode.z = -1;
	_scriptPath = scriptPath;
	_lastStateChange = 0.0f;
	_randomTimer = 0.0f;
	_updateTimer = 0.0f;
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

float AIBase::GetDistanceToNode() const
{
	return sqrt(pow(_nextNode.x - _parentTransform->GetPosition().x, 2) + pow(_nextNode.y - _parentTransform->GetPosition().y, 2) + pow(_nextNode.z - _parentTransform->GetPosition().z, 2));
}

float AIBase::GetRotationToNode() const
{
	glm::vec3 toTarget = glm::vec3(_nextNode.x, _parentTransform->GetPosition().y, _nextNode.z) - _parentTransform->GetPosition();
	float yAngle = glm::degrees(glm::angle(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	glm::vec3 cross = glm::normalize(glm::cross(_parentTransform->GetLocalFront(), glm::normalize(toTarget)));
	int s = glm::sign(cross.y);
	return yAngle * s;
}

float AIBase::GetReverseRotationToNode() const
{
	glm::vec3 toTarget = glm::vec3(_nextNode.x, _parentTransform->GetPosition().y, _nextNode.z) - _parentTransform->GetPosition();
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

glm::vec3 Test(glm::vec3 position, glm::vec3 target)
{
	return PathFinder::Instance().GeneratePath(position, target).at(0);
}

void AIBase::Update()
{
	if (Timer::GetTimeS() >= _updateTimer + 0.5f)
	{
		_updateTimer = Timer::GetTimeS();
		if (_otherTarget.x != -1 && _otherTarget.y != -1 && _otherTarget.z != -1)
		{
			auto f1 = std::async(std::launch::async, Test, _parentTransform->GetPosition(), _otherTarget);
			_nextNode = f1.get();
		}
		else if (_targetTransform != nullptr)
		{
		//	_nextNode = PathFinder::Instance().GeneratePath(_parentTransform->GetPosition(), _targetTransform->GetPosition()).at(0);
			auto f1 = std::async(std::launch::async, Test, _parentTransform->GetPosition(), _targetTransform->GetPosition());
			_nextNode = f1.get();
		}
	}

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
	lua_pushnumber(_luaState, GetDistanceToNode());
	lua_pushnumber(_luaState, GetRotationToNode());
	lua_pushnumber(_luaState, GetReverseRotationToNode());
	lua_pushnumber(_luaState, _otherTarget.x);
	lua_pushnumber(_luaState, _otherTarget.y);
	lua_pushnumber(_luaState, _otherTarget.z);
	lua_pushnumber(_luaState, Terrain::Instance().GetTerrainMaxX());
	lua_pushnumber(_luaState, Terrain::Instance().GetTerrainMaxZ());
	lua_pushnumber(_luaState, Timer::GetTimeS());
	lua_pushnumber(_luaState, Timer::GetDeltaS());
	lua_pushnumber(_luaState, _lastStateChange);
	lua_pushnumber(_luaState, _randomTimer);

	lua_call(_luaState, 16, 8); //call the function with 16 arguments and return 8 results

	if (Lua::GetStringFromStack("_state", _luaState) != GetState()) //These should probably be retreived from the functon to increase reusablilty
	{
		SetState(Lua::GetStringFromStack("_state", _luaState));
	}
	Rotate(Lua::GetFloatFromStack("rotation", _luaState));
	Move(Lua::GetFloatFromStack("fowardMovement", _luaState), Lua::GetFloatFromStack("rightMovement", _luaState));
	SetAnimation(Lua::GetIntFromStack("animation", _luaState));
	_otherTarget.x = Lua::GetFloatFromStack("_wanderPosX", _luaState);
	_otherTarget.y = Lua::GetFloatFromStack("_wanderPosY", _luaState);
	_otherTarget.z = Lua::GetFloatFromStack("_wanderPosZ", _luaState);

	Lua::CloseLua(_luaState);
}