#include "MeshComponent.h"

#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Vertex.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Mesh.h"

#include "CameraManager.h"
#include "Camera.h"

#include "SimpleMath.h"
#include <iostream>

using namespace DirectX::SimpleMath;

__declspec(align(16))
struct constant
{
	Matrix m_world;
	Matrix m_view;
	Matrix m_proj;

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
}

void MeshComponent::Update(float deltaTime)
{
	constant cc;
	cc.m_time = deltaTime;

	Matrix world = Matrix::Identity;

	if (GetOwner())
	{
		world = GetOwner()->GetTransform()->GetWorldMatrix();
	}

	Matrix view = Matrix::Identity;
	view *= CameraManager::Get()->GetActiveCamera()->GetViewMatrix();

	cc.m_world = world;
	cc.m_view = view;
	cc.m_proj = CameraManager::Get()->GetActiveCamera()->GetProjectionMatrix();

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void MeshComponent::SetMesh(Mesh* inMesh)
{
	mesh = inMesh;

	Vector3* points = new Vector3[mesh->size_list];

	for (size_t i = 0; i < mesh->size_list; i++)
	{
		points[i] = mesh->vertices[i].position;
	}

	BoundingBox::CreateFromPoints(bounds, mesh->size_list, points, sizeof(Vector3));
	//BoundingSphere::CreateFromPoints(sphereBounds, mesh->size_list, points, sizeof(Vector3));

	//sphereBounds = BoundingSphere(Vector3::Zero, 1.f);

	CalculateBounds();

	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&mesh->indices[0], mesh->size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&mesh->vertices[0], sizeof(vertex), mesh->size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void MeshComponent::CalculateBounds()
{
	if (!mesh)
		return;

	Vector3* points = new Vector3[mesh->size_list];

	for (size_t i = 0; i < mesh->size_list; i++)
	{
		points[i] = mesh->vertices[i].position;
	}

	BoundingBox::CreateFromPoints(bounds, mesh->size_list, points, sizeof(Vector3));
	bounds.Transform(bounds, GetOwner()->GetTransform()->GetWorldMatrix());
	//sphereBounds.Transform(sphereBounds, GetOwner()->GetTransform()->GetWorldMatrix());

	//std::cout << "Extents: ";
	//std::cout << "X: " << bounds.Extents.x << " Y: " << bounds.Extents.y << " Z: " << bounds.Extents.z << std::endl;
}

const BoundingBox& MeshComponent::GetBounds() const
{
	return bounds;
}

const BoundingSphere& MeshComponent::GetSphereBounds() const
{
	return sphereBounds;
}
