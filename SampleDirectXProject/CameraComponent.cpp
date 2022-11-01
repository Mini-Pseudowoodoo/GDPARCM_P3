#include "CameraComponent.h"

#include "Camera.h"
#include "CameraManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

CameraComponent::~CameraComponent()
{
	CameraManager::Get()->DestroyCamera(camera);
}

void CameraComponent::Start()
{
	Component::Start();

	camera = CameraManager::Get()->InstantiateCamera();

	if (camera)
	{
		camera->SetViewMatrix(GetOwner()->GetTransform()->GetWorldMatrix().GetInverse());
		camera->SetCameraProjection(CameraProjectionType::Perspective);
	}

	if (TransformComponent* transform = m_owner->GetTransform())
	{
		transform->GetOnSetPositionDelegate() = std::bind(&CameraComponent::UpdateViewMatrix, this);
	}
}

void CameraComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	//camera->SetViewMatrix(GetOwner()->GetTransform()->GetWorldMatrix().GetInverse());
}

void CameraComponent::SetActive() const
{
	if (camera)
	{
		CameraManager::Get()->SetActiveCamera(camera);
	}
}

void CameraComponent::UpdateViewMatrix()
{
	camera->SetViewMatrix(GetOwner()->GetTransform()->GetWorldMatrix().GetInverse());
}

Camera* CameraComponent::GetCamera() const
{
	return camera;
}
