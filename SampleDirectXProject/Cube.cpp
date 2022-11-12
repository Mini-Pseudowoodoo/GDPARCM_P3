#include "Cube.h"
#include "Vertex.h"

Cube::Cube()
{
	vertices =
	{
		//X - Y - Z
		//FRONT
		{{-0.5f,-0.5f, 0.5f},    {1,0,0}},
		{{-0.5f, 0.5f, 0.5f},    {1,1,0}},
		{{ 0.5f, 0.5f, 0.5f},    {1,1,0}},
		{{ 0.5f,-0.5f, 0.5f},    {1,0,0}},

		//BACK
		{{ 0.5f,-0.5f, -0.5f},    {1,0,1}},
		{{ 0.5f, 0.5f, -0.5f},    {0,1,1}},
		{{-0.5f, 0.5f, -0.5f},    {0,1,1}},
		{{-0.5f,-0.5f, -0.5f},    {1,0,1}},
	};

	//std::reverse(vertices.begin(), vertices.end());

	size_list = vertices.size();

	indices = 
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

	//std::reverse(indices.begin(), indices.end());

	size_index_list = indices.size();
}
