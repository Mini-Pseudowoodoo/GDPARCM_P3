#pragma once
#include "Component.h"

class RotationMovementComponent : public Component
{
public:
	RotationMovementComponent();
	~RotationMovementComponent() override;
public:
	void Start() override;
	void Update(float deltaTime) override;

public:
	void SetRotationRate(const float& inRate);

protected:
	float m_rotation_rate = 360.0f;
};
