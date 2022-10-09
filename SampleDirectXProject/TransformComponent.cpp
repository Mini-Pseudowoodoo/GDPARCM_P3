#include "TransformComponent.h"

TransformComponent::TransformComponent() : Component()
{
}

TransformComponent::~TransformComponent()
{
}

Vector3D TransformComponent::GetPosition() const
{
	return m_position;
}

Vector3D TransformComponent::GetRotation() const
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
	updateWorldMatrix();
}

void TransformComponent::SetRotation(const Vector3D& _rotation)
{
	m_rotation = _rotation;
	updateWorldMatrix();
}

void TransformComponent::SetScale(const Vector3D& _scale)
{
	m_scale = _scale;
	updateWorldMatrix();
}

void TransformComponent::updateWorldMatrix()
{
	Matrix4x4 temp;

	m_worldMatrix.setIdentity();

	temp.setIdentity();
	temp.setScale(m_scale);
	m_worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rotation.x);
	m_worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rotation.y);
	m_worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_rotation.z);
	m_worldMatrix *= temp;

	temp.setIdentity();
	temp.setTranslation(m_position);
	m_worldMatrix *= temp;
}

Matrix4x4 TransformComponent::GetWorldMatrix() const
{
	return m_worldMatrix;
}
