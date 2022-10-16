#pragma once
#include <vector>
#include<d3d11.h>

#include "Vertex.h"

class MeshComponent;

class Mesh
{
protected:
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	UINT size_list = 0;
	UINT size_index_list = 0;

protected:
	friend class MeshComponent;
};

