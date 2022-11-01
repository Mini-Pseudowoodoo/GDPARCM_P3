#pragma once
#include "CameraProjection.h"
#include "Matrix4x4.h"

class Camera
{
public:
	Camera();

public:
	Matrix4x4 GetViewMatrix() const;
	Matrix4x4 GetProjectionMatrix() const;

public:
	void SetViewMatrix(const Matrix4x4& matrix);

public:
	void SetCameraProjection(const CameraProjectionType& projection);

// Orthographic
protected:
	float orthoSize = 300.0f;
	float orthoNearPlane = 0.0f;
	float orthoFarPlane = 100.0f;

// Perspective
protected:
	float fov = 60.0f;
	float zNearPlane = 0.01f;
	float zFarPlane = 100.0f;

protected:
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
};

