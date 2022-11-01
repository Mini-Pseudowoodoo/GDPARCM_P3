#include "Camera.h"
#include "Matrix4x4.h"
#include "AppWindow.h"
#include "Matrix4x4Constants.h"

Camera::Camera() = default;

Matrix4x4 Camera::GetViewMatrix() const
{
	return viewMatrix;
}

Matrix4x4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::SetViewMatrix(const Matrix4x4& matrix)
{
	viewMatrix = matrix;
}

void Camera::SetCameraProjection(const CameraProjectionType& projection)
{
	float width, height;
	AppWindow::Get()->GetWindowSize(width, height);

	switch (projection)
	{
	case CameraProjectionType::Orthographic:
		projectionMatrix = Matrix4x4::Orthographic(width / orthoSize, height / orthoSize, orthoNearPlane, orthoFarPlane);
		break;
	case CameraProjectionType::Perspective:
		projectionMatrix = Matrix4x4::Perspective(fov, width / height, zNearPlane, zFarPlane);
		break;
	}
}
