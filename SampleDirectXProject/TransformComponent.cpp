#include "TransformComponent.h"
#include "Vector3DConstants.h"
#include "Quaternion.h"
#include "GameObject.h"

TransformComponent::TransformComponent() : Component()
{
	m_scale = Vector3D::oneVector;
}

TransformComponent::~TransformComponent() = default;

Vector3D TransformComponent::GetPosition() const
{
	return m_position;
}

Vector3D TransformComponent::GetEulerAngles() const
{
	return m_euler_angles;
}

Quaternion TransformComponent::GetRotation() const
{
	return m_rotation;
}

Vector3D TransformComponent::GetScale() const
{
	return m_scale;
}

void TransformComponent::SetPosition(const Vector3D& _position)
{
	m_position = _position;
	UpdateTransformMatrix();
}
 
void TransformComponent::SetEulerAngles(const Vector3D& _angles)
{
	m_euler_angles = _angles;
	m_rotation = Quaternion::FromEuler(_angles);
	UpdateTransformMatrix();
}

void TransformComponent::SetRotation(const Quaternion& _rotation)
{
	m_rotation = _rotation;
	m_euler_angles = Quaternion::ToEuler(_rotation);
	UpdateTransformMatrix();
}

void TransformComponent::SetScale(const Vector3D& _scale)
{
	m_scale = _scale;
	UpdateTransformMatrix();
}

void TransformComponent::UpdateTransformMatrix()
{
	Matrix4x4 temp;

	transformMatrix.setIdentity();

	temp.setIdentity();
	temp.setScale(m_scale);
	transformMatrix *= temp;

	temp.setIdentity();
	temp.setRotation(m_rotation);
	transformMatrix *= temp;

	temp.setIdentity();
	temp.setTranslation(m_position);
	transformMatrix *= temp;
}

Matrix4x4 TransformComponent::GetTransformationMatrix()
{
	return transformMatrix;
}

Matrix4x4 TransformComponent::GetWorldMatrix() const
{
	Matrix4x4 worldMatrix = Matrix4x4(transformMatrix);

	GameObject* current = this->GetOwner();

	while (GameObject* parent = current->GetParent())
	{
		current = parent;
		worldMatrix *= current->GetTransform()->GetTransformationMatrix();
	}

	return worldMatrix;
}