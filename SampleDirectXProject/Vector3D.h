#pragma once
#include <math.h>

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

	Vector3D operator +(const Vector3D& v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D operator -(const Vector3D& v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
	
	Vector3D operator *(const float& num) const
	{
		return Vector3D(x * num, y * num, z * num);
	}

	Vector3D operator /(const float& num) const
	{
		if (num == 0.0f)
			return Vector3D::zeroVector;

		return Vector3D(x / num, y / num, z / num);
	}

	void operator += (const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void operator -= (const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void operator *= (const float& num)
	{
		x *= num;
		y *= num;
		z *= num;
	}

	void operator /=(const float& num)
	{
		if (num == 0.0f)
			x = y = z = 0.0f;

		x /= num;
		y /= num;
		z /= num;
	}

	static float DotProduct(const Vector3D& a, const Vector3D& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	static Vector3D CrossProduct(const Vector3D& a, const Vector3D& b)
	{
		return Vector3D
		(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	float Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float SquareMagnitude() const
	{
		return (x * x + y * y + z * z);
	}

	void Normalize()
	{
		const float Mag = Magnitude();

		x /= Mag;
		y /= Mag;
		z /= Mag;
	}

	Vector3D ToUnitVector() const
	{
		return Vector3D(*this) / Magnitude();
	}

	//static Vector3D Lerp(const Vector3D& a, const Vector3D& b, float delta)
	//{
	//	//(A + Alpha * (B-A));
	//	return {
	//		a.x + delta * (b.x - a.x),
	//		a.y + delta * (b.y - a.y),
	//		a.z + delta * (b.z - a.z),
	//	};
	//}

	static const Vector3D zeroVector;
	static const Vector3D oneVector;
	static const Vector3D rightVector;
	static const Vector3D upVector;
	static const Vector3D forwardVector;

public:
	float x, y, z;
};