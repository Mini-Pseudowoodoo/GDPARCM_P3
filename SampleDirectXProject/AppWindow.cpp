
#include "AppWindow.h"

#include "EngineTime.h"
#include "InputSystem.h"
#include "RenderSystem.h"

#include "GameObject.h"
#include "Cube.h"
#include "Plane.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RotationMovementComponent.h"

#include "CameraManager.h"
#include "CameraComponent.h"

#include "SceneCamera.h"

// IMGUI
#include <ctype.h> 
#include <limits.h> 
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <Windows.h>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::Get()
{
	return sharedInstance;
}

void AppWindow::Initialize()
{
	sharedInstance = new AppWindow();
	
}

void AppWindow::update()
{
}

const std::vector<GameObject*>& AppWindow::GetGameObjects() const
{
	return gameObjects;
}

void AppWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));
	
	sceneCamera = new SceneCamera();
	InputSystem::get()->addListener(sceneCamera);
	sceneCamera->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 2.5f));

	GraphicsEngine::get()->init();
	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderTargets(this->m_swap_chain);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderState(this->m_swap_chain);

	Cube* cube = new Cube();
	PlaneMesh* plane = new PlaneMesh();

	/*auto* rot_1 = new RotationMovementComponent();
	rot_1->SetRotationRate(90.0f);
	auto* rot_2 = new RotationMovementComponent();
	rot_2->SetRotationRate(360.0f);*/

	gameObject_0 = GameObject::Instantiate();
	gameObject_0->SetName("Plane");
	
	MeshComponent* mesh_0 = new MeshComponent();
	gameObject_0->AttachComponent(mesh_0);
	mesh_0->SetMesh(plane);

	gameObject_1 = GameObject::Instantiate();
	gameObject_1->GetTransform()->SetPosition(Vector3::Zero);
	gameObject_1->SetName("Cube");

	MeshComponent* mesh_1 = new MeshComponent();
	gameObject_1->AttachComponent(mesh_1);
	mesh_1->SetMesh(cube);

	/*RotationMovementComponent* rot_0 = new RotationMovementComponent();
	rot_0->SetRotationRate(1.0f);
	rot_0->SetAxis(Vector3D::upVector);
	gameObject_0->AttachComponent(rot_0);*/

	gameObjects.push_back(gameObject_1);
	//gameObjects.push_back(gameObject_0);

	/*gameObject_1 = GameObject::Instantiate();
	gameObject_1->GetTransform()->SetPosition({ 1, 0, 1 });
	gameObject_1->GetTransform()->SetScale({ 0.5f, 0.5f, 0.5f });
	gameObject_1->AttachComponent(rot_1);
	gameObject_1->GetComponent<MeshComponent>()->SetMesh(cube);

	gameObject_2 = GameObject::Instantiate();
	gameObject_2->GetTransform()->SetPosition({ -1, 0, 0 });
	gameObject_2->GetTransform()->SetScale({ 0.3f, 0.3f, 0.3f });
	gameObject_2->AttachComponent(rot_2);
	gameObject_2->GetComponent<MeshComponent>()->SetMesh(cube);

	gameObject_0->AttachChild(gameObject_1);
	gameObject_1->AttachChild(gameObject_2);*/

	// LOW_VALUE - std::rand() / (RAND_MAX / HIGH_VALUE - LOW_VALUE);
	// 1 - std::rand() / (RAND_MAX / 2 - 1);


	/*GameObject* cameraObject = GameObject::Instantiate();
	CameraComponent* cameraComponent = new CameraComponent();

	cameraObject->AttachComponent(cameraComponent);
	cameraObject->GetTransform()->SetPosition(Vector3D::zeroVector);

	gameObjects.push_back(cameraObject);*/

	/*gameObject_0 = GameObject::Instantiate();
	gameObject_0->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_0->GetComponent<MeshComponent>()->SetMesh(plane);

	gameObject_1 = GameObject::Instantiate();
	gameObject_1->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_1->GetComponent<MeshComponent>()->SetMesh(cube);*/

	// Create ImGui Windows
	imObjProp = new IMObjectProperty();
	imObjProp->Initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f,0.5f, 1);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearDepthStencilView(this->m_swap_chain);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	const float deltaTime = EngineTime::getDeltaTime();

	// Update scene camera
	sceneCamera->Update(deltaTime);

	for (GameObject* gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	// Render ImGui
	imObjProp->Render(sceneCamera->GetSelectedObj());

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::get()->release();
	InputSystem::get()->removeListener(sceneCamera);

	for (GameObject* gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();

	delete sceneCamera;
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(sceneCamera);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(sceneCamera);
}
