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
	UpdateTransformMatrix();
}
 
void TransformComponent::SetEulerAngles(const Vector3& _angles)
{
	m_euler_angles = _angles;
	m_rotation = Quaternion::CreateFromYawPitchRoll(_angles);
	UpdateTransformMatrix();
}

void TransformComponent::SetRotation(const Quaternion& _rotation)
{
	m_rotation = _rotation;
	m_euler_angles = _rotation.ToEuler();
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

	/*temp = Matrix::Identity;
	temp = Matrix::CreateRotationX(m_euler_angles.x);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateRotationY(m_euler_angles.y);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateRotationZ(m_euler_angles.z);
	transformMatrix *= temp;*/

	temp = Matrix::Identity;
	temp = Matrix::CreateFromQuaternion(m_rotation);
	transformMatrix *= temp;

	temp = Matrix::Identity;
	temp = Matrix::CreateTranslation(m_position);
	transformMatrix *= temp;
}

Matrix TransformComponent::GetTransformationMatrix()
{
	return transformMatrix;
}

Matrix TransformComponent::GetLocalToWorldMatrix() const
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

Matrix TransformComponent::GetWorldToLocalMatrix() const
{
	Matrix invWorld = GetLocalToWorldMatrix().Invert();
	return invWorld;
}

void TransformComponent::SetTransformationMatrix(Matrix m)
{
	transformMatrix = m;

	m.Decompose(m_scale, m_rotation, m_position);
	m_euler_angles = m_rotation.ToEuler();
}