#include "GameObject.h"
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

GameObject* GameObject::GetRoot()
{
	GameObject* current = this;

	while (GameObject* parent = current->GetParent())
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
	m_parent = _parent;
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
	auto* obj = new GameObject();
	obj->Start();
	return obj;
}
