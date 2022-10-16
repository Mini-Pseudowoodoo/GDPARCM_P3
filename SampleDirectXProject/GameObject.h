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
	GameObject* GetRoot();
	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

public:
	virtual void Start();
	virtual void Update(float deltaTime);

	template <class T>
	T* GetComponent();

private:
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
