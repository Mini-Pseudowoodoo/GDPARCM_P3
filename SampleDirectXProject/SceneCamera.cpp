#include "SceneCamera.h"
#include "Camera.h"
#include "CameraManager.h"
#include "CameraComponent.h"
#include "Matrix4x4.h"
#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "Camera.h"
#include "TransformComponent.h"

#include <iostream>

SceneCamera::SceneCamera() : GameObject()
{
	camera = new CameraComponent();
	camera->SetActive();
	AttachComponent(camera);
}

SceneCamera::~SceneCamera()
{
	GameObject::~GameObject();
}

void SceneCamera::Start()
{
	GameObject::Start();

}

void SceneCamera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	if (transform)
	{
		const Vector3D moveInput = input.ToUnitVector() * cameraSpeed;

		const Matrix4x4& mat = transform->GetTransformationMatrix();

		Vector3D new_pos = mat.getTranslation() + mat.getZDirection() * (moveInput.z);

		new_pos = new_pos + mat.getXDirection() * (moveInput.x);

		new_pos = new_pos + mat.getYDirection() * (moveInput.y);

		transform->SetPosition(new_pos);
	}
}

void SceneCamera::onKeyDown(int key)
{
	if (key == 'W')
	{
		input.z = 1.0f;
	}

	else if (key == 'S')
	{
		input.z = -1.0f;
	}

	else if (key == 'A')
	{
		input.x = -1.0f;
	}

	else if (key == 'D')
	{
		input.x = 1.0f;
	}

	else if (key == 'Q')
	{
		input.y = -1.0f;
	}

	else if (key == 'E')
	{
		input.y = 1.0f;
	}

	/*if (key == '1')
	{
		if (camera)
		{
			camera->GetCamera()->SetCameraProjection(CameraProjectionType::Orthographic);
		}
	}
	else if (key == '2')
	{
		if (camera)
		{
			camera->GetCamera()->SetCameraProjection(CameraProjectionType::Perspective);
		}
	}*/

}

void SceneCamera::onKeyUp(int key)
{
	input = Vector3D::zeroVector;
}

void SceneCamera::onMouseMove(const Point& delta_mouse)
{
	if (!rmbDown)
		return;

	float width, height;
	AppWindow::Get()->GetWindowSize(width, height);

	Vector3D euler = transform->GetEulerAngles();

	const float deltaTime = EngineTime::getDeltaTime();

	euler.y += (delta_mouse.x - (width / 2.0f)) * deltaTime;
	euler.x += (delta_mouse.y - (height / 2.0f)) * deltaTime;

	if (transform)
	{
		transform->SetEulerAngles(euler);
	}

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void SceneCamera::onLeftMouseButtonDown(const Point& mouse_pos)
{
}

void SceneCamera::onLeftMouseButtonUp(const Point& mouse_pos)
{
}

void SceneCamera::onRightMouseButtonDown(const Point& mouse_pos)
{
	rmbDown = true;
	InputSystem::get()->showCursor(false);
}

void SceneCamera::onRightMouseButtonUp(const Point& mouse_pos)
{
	rmbDown = false;
	InputSystem::get()->showCursor(true);
}
