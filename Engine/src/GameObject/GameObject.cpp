

#include "GameObject.h"
#include "Component.h"
#include "..\Graphics\Shader.h"
#include "..\Core\Camera.h"
#include "..\Components\MeshRenderer.h"
#include "..\Core\Timer.h"



GameObject::GameObject(std::string name, bool isActive, unsigned int layer, GameObject* parent) : transform(Transform(this))
{
	SetName(name);
	SetActive(isActive);
	SetLayer(layer);
	SetParent(parent);
	SetIsSelfManaged(false, true);
	SetIsStatic(0);
	flashing = 0;
}

GameObject::~GameObject()
{
	//Destroy components
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}

	_components.clear();
	//Logger::LogWarning("Gameobject", GetName(), "deleted");
}



void GameObject::SetName(std::string name)
{
	if (name.length() > 0)
	{
		_name = name;
		_parent = nullptr;
		_layer = Layers::DEFAULT;
	}
}

void GameObject::FlagToBeDestroyed()
{
//	SetActive(false);
	_toBeDestroyed = true;

	for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
		(*it)->FlagToBeDestroyed();
		}
	
}

void GameObject::OnAddToScene(Scene& scene)
{
	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		(*it)->OnGameObjectAddedToScene(this);
	}


	for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
		(*it)->OnAddToScene(scene);
		}
	
}

void GameObject::SetIsSelfManaged(bool sm, bool includeChildren)
{

	_isSelfManaged = sm;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetIsSelfManaged(sm, includeChildren);
		}
	}
}

void GameObject::SetActive(bool active, bool includeChildren)
{
	_isActive = active;

	for (auto it = std::begin(_components); it != std::end(_components); it++)
	{
		(*it)->SetActive(active);
	}

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetActive(active,includeChildren);
		}
	}
}

void GameObject::SetIsStatic(bool st, bool includeChildren)
{
	_isStatic = st;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetIsStatic(st, includeChildren);
		}
	}
}

void GameObject::SetLayer(unsigned int layer, bool includeChildren)
{
	if (layer == 0)
		_layer = 0;
	else
	_layer |= layer;

	if (includeChildren == true)
	{
		for (auto it = std::begin(_children); it != std::end(_children); it++)
		{
			(*it)->SetLayer(layer, includeChildren);
		}
	}
}

void GameObject::SetParent(GameObject *parent)
{
	if (parent != this)
	{
		_parent = parent;
	}
}

void GameObject::FlashColor(float r, float g, float b)
{
	ApplyColor(r,g,b);
	colorTimer = 0.1f;
	flashing = 1;
}


std::string GameObject::GetName() const
{
	return _name;
}

bool GameObject::GetActive() const
{
	return _isActive;
}

bool GameObject::GetToBeDestroyed() const
{
	return _toBeDestroyed;
}


unsigned int GameObject::GetLayer() const
{
	return _layer;
}

GameObject* GameObject::GetParent() const
{
	return _parent;
}

void GameObject::AddChild(GameObject* child)
{
	//if (HasChild(child->GetName()) == false)
	//{
		child->SetParent(this);
		child->transform.parent = &transform;
		_children.push_back(child);
	//}
}

Component* GameObject::AddComponent(Component* component)
{
	//if (HasComponent(component->GetName()) == false)
	//{
		component->SetParent(this);
		_components.push_back(component);

		component->OnAttach(this);
		return component;
	//}
}

void GameObject::AddComponentToChild(Component* component)
{

}

void GameObject::RemoveChild(std::string childName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->SetParent(nullptr);
		_children.remove_if([&](GameObject* gameObject) {return gameObject->GetName() == childName; });
	}
}

void GameObject::RemoveComponent(std::string componentName)
{
	if (HasComponent(componentName) == true)
	{
		auto it = std::remove_if(std::begin(_components), std::end(_components), [&](Component* component) {return component->GetName() == componentName; });
		_components.erase(it, std::end(_components));
	}
}

void GameObject::RemoveComponentInChild(std::string childName, std::string componentName)
{
	if (HasChild(childName) == true)
	{
		GetChild(childName)->RemoveComponent(componentName);
	}
}

GameObject* GameObject::GetChild(std::string childName) const
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* gameObject) -> GameObject* {if (gameObject->GetName() == childName){ return gameObject; } else { return nullptr; }});

	if (it != std::end(_children))
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}


std::list<GameObject*>& GameObject::GetChildList()
{
	return _children;
}

std::list<Component*>& GameObject::GetComponentList()
{
	return _components;
}

bool GameObject::HasChild(std::string childName) const
{
	std::list<GameObject*>::const_iterator it;
	it = std::find_if(std::begin(_children), std::end(_children), [&](GameObject* child) {return child->GetName() == childName; });

	if (it != std::end(_children))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameObject::HasComponent(std::string componentName) const
{
	std::list<Component*>::const_iterator it;
	it = std::find_if(std::begin(_components), std::end(_components), [&](Component* const component) {return component->GetName() == componentName; });

	if (it != std::end(_components))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameObject::ChildHasComponent(std::string childName, std::string componentName) const
{
	return false; //Temp
}

void GameObject::Update()
{
	// If i't static, update transform for the first 2 ticks only
	if (Timer::GetTickCount() <= 1 || !_isStatic)
	{
		transform.Update();
	}

	colorTimer = colorTimer < 0 ? 0 : colorTimer - Timer::GetDeltaS();
	if (colorTimer == 0 && flashing)
	{
		ApplyColor(1,1,1);
		flashing = 0;
	}

	auto it = _children.begin();
	for (; it != _children.end(); it++)
		if ((*it)->GetActive() == true)
			(*it)->Update();

	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		if ((*itc)->GetActive() == true)
			(*itc)->Update();
}

void GameObject::EngineUpdate()
{


	auto it = _children.begin();
	for (; it != _children.end(); it++)
		(*it)->EngineUpdate();

	auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		(*itc)->EngineUpdate();
}

void GameObject::LateUpdate()
{


	auto it = _children.begin();
	for (; it != _children.end(); it++)
		(*it)->LateUpdate();

	/*auto itc = _components.begin();
	for (; itc != _components.end(); itc++)
		(*itc)->LateUpdate();*/
}



void GameObject::PrintHierarchy()
{
	std::string o = "\n";
	PrintHierarchy(0, o);
	Logger::LogInfo("{}", o);
}

void GameObject::PrintHierarchy(int indentation, std::string& output)
{
	for (int i = 0; i < indentation; i++)
		output += "...";

	output += GetName();

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		output += "\n";
		(*it)->PrintHierarchy(indentation + 1, output);
	}
}

GameObject* GameObject::GetRoot()
{
	if (_parent == nullptr)
		return this;
	else
	{
		return _parent->GetRoot();
	}
}

void GameObject::ApplyColor(float r, float g, float b)
{
	Renderer* rend = (GetComponentByType<Renderer>("Renderer"));

	if (rend != nullptr)
	{
		rend->GetMaterial(MaterialType::DEFAULT).SetColor(r, g, b);
		rend->GetMaterial(MaterialType::NOLIGHT).SetColor(r, g, b);
		rend->GetMaterial(MaterialType::COLORONLY).SetColor(r, g, b);
		//Logger::LogInfo("Applied material!");
	}

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		(*it)->ApplyColor(r,g,b);
	}
}


void GameObject::ApplyMaterial(Material mat, MaterialType mt)

{
	Renderer* r = (GetComponentByType<Renderer>("Renderer"));	

	if (r != nullptr)
	{
		r->SetMaterial(mat, mt);
		
		//Logger::LogInfo("Applied material!");
	}

	auto it = _children.begin();

	for (; it != _children.end(); it++)
	{
		(*it)->ApplyMaterial(mat, mt);
	}
}
