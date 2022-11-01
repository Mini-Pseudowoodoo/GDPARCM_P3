#pragma once
#include "Component.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class RotationMovementComponent : public Component
{
public:
	RotationMovementComponent();
	~RotationMovementComponent() override;
public:
	void Start() override;
	void Update(float deltaTime) override;

public:
	void SetAxis(const Vector3& inAxis);
	void SetRotationRate(const float& inRate);

protected:
	Vector3 axis;
	float m_rotation_rate = 360.0f;
};
