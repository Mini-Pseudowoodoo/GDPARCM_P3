﻿#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"

GameObject::GameObject()
{
	transform = new TransformComponent();
	AttachComponent(transform);
}

GameObject::~GameObject()
{
	for(auto* component : m_components)
	{
		DetachComponent(component);
	}
}

void GameObject::AttachChild(GameObject* _child)
{
	_child->SetParent(this);
	m_children.push_back(_child);
}

void GameObject::DetachChild(GameObject* _child)
{
	_child->SetParent(nullptr);
	auto i = remove(m_children.begin(), m_children.end(), _child);
}

void GameObject::RemoveFromParent()
{
	if (m_parent)
	{
		m_parent->DetachChild(this);
		m_parent = nullptr;
	}
}

bool GameObject::IsChildOf(GameObject* _parent)
{
	return m_parent == _parent;
}

void GameObject::AttachComponent(Component* _component)
{
	_component->SetOwner(this);
	_component->Start();
	m_components.push_back(_component);
}

void GameObject::DetachComponent(Component* _component)
{
	_component->SetOwner(nullptr);
	auto i = remove(m_components.begin(), m_components.end(), _component);
}

bool GameObject::IsRoot() const
{
	return !m_parent;
}

std::string GameObject::GetName() const
{
	return name;
}

void GameObject::SetName(const std::string& _name)
{
	name = _name;
}

GameObject* GameObject::GetRoot() const
{
	GameObject* current = nullptr;

	while (GameObject* parent = this->GetParent())
	{
		current = parent;
	}

	return current;
}

GameObject* GameObject::GetParent() const
{
	return m_parent;
}

void GameObject::SetParent(GameObject* _parent)
{
	if (!IsChildOf(_parent))
	{
		m_parent = _parent;
		m_parent->AttachChild(this);
	}
}

void GameObject::Start()
{
	for (auto* component : m_components)
	{
		component->Start();
	}

	for (auto* child : m_children)
	{
		child->Start();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto* component : m_components)
	{
		component->Update(deltaTime);
	}

	for (auto* child : m_children)
	{
		child->Update(deltaTime);
	}
}

TransformComponent* GameObject::GetTransform() const
{
	return transform;
}

GameObject* GameObject::Instantiate()
{
	GameObject* obj = new GameObject();
	obj->Start();
	return obj;
}

GameObject* GameObject::Instantiate(std::string _name)
{
	GameObject* obj = new GameObject();
	obj->Start();
	obj->SetName(_name);
	return obj;
}
