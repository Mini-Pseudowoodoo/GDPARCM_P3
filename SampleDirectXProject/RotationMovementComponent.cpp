#include "RotationMovementComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

RotationMovementComponent::RotationMovementComponent()
{
}

RotationMovementComponent::~RotationMovementComponent()
{
}

void RotationMovementComponent::Start()
{
	Component::Start();
}

void RotationMovementComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	if (!GetOwner() || !GetOwner()->transform)
		return;

	const Vector3D& currentRotation = GetOwner()->transform->GetRotation();
	const Vector3D& newRotation = { currentRotation.x, currentRotation.y + (m_rotation_rate * deltaTime), currentRotation.z};

	GetOwner()->transform->SetRotation(newRotation);
}

void RotationMovementComponent::SetRotationRate(const float& inRate)
{
	m_rotation_rate = inRate;
}
