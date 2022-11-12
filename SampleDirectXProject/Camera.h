#pragma once
#include "CameraProjection.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class Camera
{
public:
	Camera();

public:
	Matrix GetViewMatrix() const;
	Matrix GetProjectionMatrix() const;

public:
	Ray ScreenPointToRay(Vector3 point);

public:
	void SetViewMatrix(const Matrix& matrix);

public:
	void SetCameraProjection(const CameraProjectionType& projection);

// Orthographic
protected:
	float orthoSize = 300.0f;
	float orthoNearPlane = 0.0f;
	float orthoFarPlane = 100.0f;

// Perspective
protected:
	float fov = 1.57f;
	float zNearPlane = 0.01f;
	float zFarPlane = 100.0f;

protected:
	Matrix viewMatrix;
	Matrix projectionMatrix;
};

