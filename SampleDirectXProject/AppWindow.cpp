
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

#include <Windows.h>

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;

	unsigned int m_time;
};


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

void AppWindow::update()
{
	//constant cc;
	//cc.m_time = ::GetTickCount();

	Matrix4x4 temp;

	//cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_right * 0.1f);

	new_pos = new_pos + world_cam.getYDirection() * (m_up * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;
	
	world_cam.inverse();

	m_view_matrix = world_cam;

	//cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
	//cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	m_projection_matrix.setPerspectiveFovLH(90, ((float)width / (float)height), 0.01f, 100.0f);

	//m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 1.f * m_delta_time;
		m_forward = 1.0f;
	}

	if (key == 'S')
	{
		//m_rot_x -= 1.f * m_delta_time;
		m_forward = -1.0f;
	}

	if (key == 'A')
	{
		//m_rot_y += 1.f * m_delta_time;
		m_right = -1.0f;
	}

	if (key == 'D')
	{
		//m_rot_y -= 1.f * m_delta_time;
		m_right = 1.0f;
	}

	if (key == 'Q')
	{
		m_up = 1.0f;
	}

	if (key == 'E')
	{
		m_up = -1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;
	m_up = 0.0f;
}

void AppWindow::onMouseMove(const Point& delta_mouse)
{
	if (!m_rmb_down)
		return;

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (delta_mouse.y - (height / 2.0f)) * m_delta_time;
	m_rot_y += (delta_mouse.x - (width / 2.0f)) * m_delta_time;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseButtonDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseButtonUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseButtonDown(const Point& mouse_pos)
{
	m_rmb_down = true;
	InputSystem::get()->showCursor(false);
}

void AppWindow::onRightMouseButtonUp(const Point& mouse_pos)
{
	m_rmb_down = false;
	InputSystem::get()->showCursor(true);
}

Matrix4x4 AppWindow::GetViewMatrix() const
{
	return m_view_matrix;
}

Matrix4x4 AppWindow::GetProjectionMatrix() const
{
	return m_projection_matrix;
}

void AppWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));
	InputSystem::get()->addListener(this);

	GraphicsEngine::get()->init();
	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderTargets(this->m_swap_chain);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	Cube* cube = new Cube();
	Plane* plane = new Plane();

	auto* rot_0 = new RotationMovementComponent();
	rot_0->SetRotationRate(15.0f);
	auto* rot_1 = new RotationMovementComponent();
	rot_1->SetRotationRate(90.0f);
	auto* rot_2 = new RotationMovementComponent();
	rot_2->SetRotationRate(360.0f);

	gameObject_0 = GameObject::Instantiate();
	gameObject_0->GetTransform()->SetPosition({ 0, 0, 0 });
	gameObject_0->AttachComponent(rot_0);
	gameObject_0->GetComponent<MeshComponent>()->SetMesh(cube);

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

	/*for (int i = 0; i < 100; i++)
	{
		GameObject* gameObject = GameObject::Instantiate();

		const float randomX = -5.0f + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX / (5.0f - -5.0f));
		const float randomY = -5.0f + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX / (5.0f - -5.0f));
		const float randomZ = -0.05f + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX / (0.05f - -0.05f));
		gameObject->GetTransform()->SetPosition(Vector3D(randomX, randomY , randomZ));
		gameObject->GetComponent<MeshComponent>()->SetMesh(cube);

		RotationMovementComponent* rot = new RotationMovementComponent();
		rot->SetRotationRate(15.0f);
		gameObject->AttachComponent(rot);

		gameObjects.push_back(gameObject);
	}*/

	/*gameObject_0 = GameObject::Instantiate();
	gameObject_0->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_0->GetComponent<MeshComponent>()->SetMesh(plane);

	gameObject_1 = GameObject::Instantiate();
	gameObject_1->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_1->GetComponent<MeshComponent>()->SetMesh(cube);*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f,0.5f, 1);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearDepthStencilView(this->m_swap_chain);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();
	gameObject_0->Update(m_delta_time);
	/*gameObject_1->Update(m_delta_time);
	gameObject_2->Update(m_delta_time);*/

	/*for (GameObject* gameObject : gameObjects)
	{
		gameObject->Update(m_delta_time);
	}*/

	/*gameObject_0->Update(m_delta_time);
	gameObject_1->Update(m_delta_time);*/

	/*GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);*/
	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = static_cast<float>(::GetTickCount());
	m_delta_time = (m_old_delta) ? (m_new_delta - m_old_delta) / 1000.0f : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::get()->removeListener(this);

	/*m_vb->release();
	m_ib->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();*/
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}
