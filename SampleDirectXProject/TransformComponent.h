#pragma once
#include "Component.h"
#include <functional>

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent() override;

public:
	Vector3 m_position;
	Vector3 m_euler_angles;
	Quaternion m_rotation;
	Vector3 m_scale;
	Matrix transformMatrix;

public:
	Vector3 GetPosition() const;
	Vector3 GetEulerAngles() const;
	Quaternion GetRotation() const;
	Vector3 GetScale() const;

	void SetPosition(const Vector3& _position);
	void SetEulerAngles(const Vector3& _angles);
	void SetRotation(const Quaternion& _rotation);
	void SetScale(const Vector3& _scale);
public:
	void UpdateTransformMatrix();
	Matrix GetTransformationMatrix();
	Matrix GetWorldMatrix() const;
	Matrix GetLocalMatrix() const;

private:
	std::function<void()> OnSetPosition;

public:
	std::function<void()>& GetOnSetPositionDelegate();
};
