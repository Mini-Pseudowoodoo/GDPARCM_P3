#pragma once

class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0)
	{
		
	}

	Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}

	Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z)
	{
		
	}

	~Vector3D()
	{

	}

	Vector3D operator *(float num)
	{
		return Vector3D(x * num, y * num, z * num);
	}

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	static Vector3D lerp(const Vector3D& a, const Vector3D& b, float delta)
	{
		return {
			a.x * (1.0f - delta) + b.x * (delta),
			a.y * (1.0f - delta) + b.y * (delta),
			a.z * (1.0f - delta) + b.z * (delta),
		};
	}

public:
	float x, y, z;
};