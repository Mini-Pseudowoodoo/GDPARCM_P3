#include "Camera.h"
#include "AppWindow.h"

#include <iostream>

Camera::Camera() = default;

Matrix Camera::GetViewMatrix() const
{
	return viewMatrix;
}

Matrix Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

Ray Camera::ScreenPointToRay(Vector3 point)
{
	float width, height;
	AppWindow::Get()->GetWindowSize(width, height);

	float x = (((2.0f * point.x) / width) - 1.0f) / projectionMatrix._11;
	float y = ((((2.0f * point.y) / height) - 1.0f) * -1.0f) / projectionMatrix._22;


	Matrix view = viewMatrix;
	Matrix invView = view.Invert();

	Ray r;
	r.position = Vector3::Zero;

	r.direction.x = (x * invView._11) + (y * invView._21) + invView._31;
	r.direction.y = (x * invView._12) + (y * invView._22) + invView._32;
	r.direction.z = -((x * invView._13) + (y * invView._23) + invView._33);

	r.direction = Vector3(x, y, -1);


	r.position = Vector3::Transform(r.position, invView);
	r.direction = Vector3::TransformNormal(r.direction, invView);
	r.direction.Normalize();

	/*std::cout << "POS: " << std::endl;
	std::cout << "X: " << r.position.x << " Y: " << r.position.y << " Z: " << r.position.z << std::endl;

	std::cout << "DIR: " << std::endl;
	std::cout << "X: " << r.direction.x << " Y: " << r.direction.y << " Z: " << r.direction.z << std::endl;*/

	return r;
}

void Camera::SetViewMatrix(const Matrix& matrix)
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
		projectionMatrix = Matrix::CreateOrthographic(width / orthoSize, height / orthoSize, orthoNearPlane, orthoFarPlane);
		break;
	case CameraProjectionType::Perspective:
		projectionMatrix = Matrix::CreatePerspectiveFieldOfView(fov, width / height, zNearPlane, zFarPlane);
		break;
	}
}
