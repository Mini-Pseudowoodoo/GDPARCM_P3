#pragma once
#include "Component.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent() override;

public:
	Vector3D m_position;
	Vector3D m_rotation;
	Vector3D m_scale = Vector3D(1, 1, 1);
	Matrix4x4 m_worldMatrix;

public:
	Vector3D GetPosition() const;
	Vector3D GetRotation() const;
	Vector3D GetScale() const;

	void SetPosition(const Vector3D& _position);
	void SetRotation(const Vector3D& _rotation);
	void SetScale(const Vector3D& _scale);
public:
	void updateWorldMatrix();
	Matrix4x4 GetWorldMatrix() const;
};
