#pragma once

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};
