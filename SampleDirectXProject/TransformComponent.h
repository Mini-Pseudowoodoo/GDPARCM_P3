#pragma once
#include "Component.h"
#include "EngineMath.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent() override;

public:
	Vector3D m_position;
	Vector3D m_euler_angles;
	Quaternion m_rotation;
	Vector3D m_scale;
	Matrix4x4 transformMatrix;

public:
	Vector3D GetPosition() const;
	Vector3D GetEulerAngles() const;
	Quaternion GetRotation() const;
	Vector3D GetScale() const;

	void SetPosition(const Vector3D& _position);
	void SetEulerAngles(const Vector3D& _angles);
	void SetRotation(const Quaternion& _rotation);
	void SetScale(const Vector3D& _scale);
public:
	void UpdateTransformMatrix();
	Matrix4x4 GetTransformationMatrix();
	Matrix4x4 GetWorldMatrix() const;
	Matrix4x4 GetLocalMatrix() const;
};
