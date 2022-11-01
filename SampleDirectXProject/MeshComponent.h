#pragma once
#include "Component.h"

class ConstantBuffer;
class PixelShader;
class VertexShader;
class IndexBuffer;
class VertexBuffer;

class Mesh;

class MeshComponent: public Component
{
public:
	MeshComponent();
	~MeshComponent() override;

public:
	void Start() override;
	void Update(float deltaTime) override;
	void SetMesh(Mesh* inMesh);

protected:
	Mesh* mesh = nullptr;

protected:
	VertexBuffer* m_vb = nullptr;
	IndexBuffer* m_ib = nullptr;
	VertexShader* m_vs = nullptr;
	PixelShader* m_ps = nullptr;
	ConstantBuffer* m_cb = nullptr;

protected:
	friend class Mesh;
};
