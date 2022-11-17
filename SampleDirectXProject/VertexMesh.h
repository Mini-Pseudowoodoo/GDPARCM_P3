#pragma once
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class VertexMesh
{
public:
	VertexMesh() :position(), texcoord()
	{
	}
	VertexMesh(Vector3 _position, Vector2 _texcoord) :position(_position), texcoord(_texcoord)
	{
	}
	VertexMesh(const VertexMesh& vertex) :position(vertex.position), texcoord(vertex.texcoord)
	{
	}
	~VertexMesh()
	{
	}
public:
	Vector3 position;
	Vector2 texcoord;
};
