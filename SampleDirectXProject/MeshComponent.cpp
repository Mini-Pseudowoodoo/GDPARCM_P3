#include "MeshComponent.h"

#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Matrix4x4.h"
#include "Vertex.h"
#include "GameObject.h"
#include "TransformComponent.h"

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;

	unsigned int m_time;
};


MeshComponent::MeshComponent() : Component()
{

}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::Start()
{
	Component::Start();

	vertex list[] =
	{
		//X - Y - Z
		//FRONT
		{{-0.5f,-0.5f,-0.5f},    {1,0,0}},
		{{-0.5f, 0.5f,-0.5f},    {0,1,0}},
		{{ 0.5f, 0.5f,-0.5f},    {0,0,1}},
		{{ 0.5f,-0.5f,-0.5f},    {0,1,1}},

		//BACK
		{{ 0.5f,-0.5f, 0.5f},    {1,1,0}},
		{{ 0.5f, 0.5f, 0.5f},    {1,0,1}},
		{{-0.5f, 0.5f, 0.5f},    {1,1,1}},
		{{-0.5f,-0.5f, 0.5f},    {0,0,0}},
	};

	UINT size_list = ARRAYSIZE(list);

	unsigned int index_list[] =
	{
		//Front
		0, 1, 2,
		2, 3, 0,
		//Back
		4, 5, 6,
		6, 7, 4,
		//Top
		1, 6, 5,
		5, 2, 1,
		//Bottom
		7, 0, 3,
		3, 4, 7,
		//Right
		3, 2, 5,
		5, 4, 3,
		//Left
		7, 6, 1,
		1, 0, 7,
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void MeshComponent::Update(float deltaTime)
{
	constant cc;
	cc.m_time = ::GetTickCount();

	Matrix4x4 world;
	world.setIdentity();

	GameObject* _owner = GetOwner();

	while (_owner != nullptr)
	{
		world *= _owner->transform->GetWorldMatrix();
		_owner = _owner->GetParent();
	}

	cc.m_world = world;
	cc.m_view = AppWindow::getInstance()->GetViewMatrix();
	cc.m_proj = AppWindow::getInstance()->GetProjectionMatrix();

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}
