#include "Plane.h"

Plane::Plane()
{
	vertices =
	{
		//X - Y - Z
		{{5.0f, 0.0f, 5.0f},    {1,1,1}},
		{{-5.0f, 0.0f, 5.0f},    {1,1,1}},
		{{5.0f, 0.0f, -5.0f},    {1,1,1}},
		{{-5.0f, 0.0f, -5.0f},    {1,1,1}},
	};


	size_list = vertices.size();

	indices =
	{
		2, 3, 0,
		1, 0, 3,
	};

	size_index_list = indices.size();
}
