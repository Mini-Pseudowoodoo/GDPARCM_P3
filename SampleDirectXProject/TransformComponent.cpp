#include "TransformComponent.h"
#include "MeshComponent.h"
#include "GameObject.h"
#include <iostream>

TransformComponent::TransformComponent() : Component()
{
	m_scale = Vector3::One;
}

TransformComponent::~TransformComponent() = default;

Vector3 TransformComponent::GetPosition() const
{
	return m_position;
}

Vector3 TransformComponent::GetEulerAngles() const
{
	return m_euler_angles;
}

Quaternion TransformComponent::GetRotation() const
{
	return m_rotation;
}

Vector3 TransformComponent::GetScale() const
{
	return m_scale;
}

void TransformComponent::SetPosition(const Vector3& _position)
{
	m_position = _position;
	if (OnSetPosition)
		OnSetPosition();
	UpdateTransformMatrix();
}
 
void TransformComponent::SetEulerAngles(const Vector3& _angles)
{
	m_euler_angles = _angles;
	m_rotation.CreateFromYawPitchRoll(_angles);
	UpdateTransformMatrix();
}

void TransformComponent::SetRotation(const Quaternion& _rotation)
{
	Quaternion rot = _rotation;
	rot.Normalize();

	m_rotation = rot;
	m_euler_angles = rot.ToEuler();
	UpdateTransformMatrix();
}

void TransformComponent::SetScale(const Vector3& _scale)
{
	m_scale = _scale;
	UpdateTransformMatrix();
}

void TransformComponent::UpdateTransformMatrix()
{
	Matrix temp;

	transformMatrix = Matrix::Identity;

	temp = Matrix::Identity;
	temp = Matrix::CreateScale(m_scale);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateRotationX(m_euler_angles.x);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateRotationY(m_euler_angles.y);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateRotationZ(m_euler_angles.z);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateTranslation(m_position);
	transformMatrix *= temp;

	if (MeshComponent* mesh = GetOwner()->GetComponent<MeshComponent>())
	{
		mesh->CalculateBounds();
	}
}

Matrix TransformComponent::GetTransformationMatrix()
{
	return transformMatrix;
}

Matrix TransformComponent::GetWorldMatrix() const
{
	Matrix worldMatrix = transformMatrix;

	GameObject* current = this->GetOwner();

	while (GameObject* parent = current->GetParent())
	{
		current = parent;
		worldMatrix *= current->GetTransform()->GetTransformationMatrix();
	}

	return worldMatrix;
}

Matrix TransformComponent::GetLocalMatrix() const
{
	Matrix invWorld = GetWorldMatrix().Invert();
	return invWorld;
}

std::function<void()>& TransformComponent::GetOnSetPositionDelegate()
{
	return OnSetPosition;
}
