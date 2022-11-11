#pragma once
#include <vector>
#include <string>

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
	void RemoveFromParent();
	bool IsChildOf(GameObject* _parent);
	void AttachComponent(Component* _component);
	void DetachComponent(Component* _component);

	bool IsRoot() const;

public:
	std::string GetName() const;
	void SetName(const std::string& _name);

public:
	GameObject* GetRoot() const;
	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

public:
	virtual void Start();
	virtual void Update(float deltaTime);

	template <class T>
	T* GetComponent();

protected:
	std::string name = "GameObject";
	TransformComponent* transform = nullptr;
public:
	TransformComponent* GetTransform() const;

protected:
	std::vector<GameObject*> m_children;
	std::vector<Component*> m_components;

protected:
	GameObject* m_parent = nullptr;

public:
	static GameObject* Instantiate();
	static GameObject* Instantiate(std::string _name);
};

template <class T>
T* GameObject::GetComponent()
{
	for (auto* component : m_components)
	{
		if (T* comp = dynamic_cast<T*>(component))
		{
			return comp;
		}
	}

	return nullptr;
}
