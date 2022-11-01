#pragma once
#include "Component.h"
#include "Vector3D.h"

class RotationMovementComponent : public Component
{
public:
	RotationMovementComponent();
	~RotationMovementComponent() override;
public:
	void Start() override;
	void Update(float deltaTime) override;

public:
	void SetAxis(const Vector3D& inAxis);
	void SetRotationRate(const float& inRate);

protected:
	Vector3D axis;
	float m_rotation_rate = 360.0f;
};
