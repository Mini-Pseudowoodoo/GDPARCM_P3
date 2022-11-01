#include "RotationMovementComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <iostream>

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

	if (!GetOwner())
		return;

	TransformComponent* transform = GetOwner()->GetTransform();

	if (!transform)
		return;

	const Vector3D currentRotation = transform->GetEulerAngles();
	const Vector3D newRotation = currentRotation + (axis * m_rotation_rate);

	const Quaternion currentQuat = transform->GetRotation();
	const Quaternion newQuat = Quaternion::FromEuler(newRotation);
	//const Quaternion delta = Quaternion::FromEuler(Vector3D(0, m_rotation_rate * deltaTime, 0));

	/*std::cout << "Current: \n";
	std::cout << "X:" << currentQuat.x << " Y: " << currentQuat.y << " Z: " << currentQuat.z << " W: " << currentQuat.w << std::endl;
	std::cout << "New: \n";
	std::cout << "X:" << newQuat.x << " Y: " << newQuat.y << " Z: " << newQuat.z << " W: " << newQuat.w << std::endl;*/

	transform->SetEulerAngles(newRotation);
	//transform->SetRotation(newQuat);
}

void RotationMovementComponent::SetAxis(const Vector3D& inAxis)
{
	axis = inAxis.ToUnitVector();
}

void RotationMovementComponent::SetRotationRate(const float& inRate)
{
	m_rotation_rate = inRate;
}
