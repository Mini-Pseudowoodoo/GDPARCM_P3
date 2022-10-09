#pragma once
#include <vector>

class Component;
class TransformComponent;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void AttachChild(GameObject* _child);
	void DetachChild(GameObject* _child);
	void AttachComponent(Component* _component);
	void DetachComponent(Component* _component);

public:
	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

public:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	TransformComponent* transform = nullptr;

protected:
	std::vector<GameObject*> m_children;
	std::vector<Component*> m_components;

protected:
	GameObject* m_parent = nullptr;

public:
	static GameObject* Instantiate();
};
