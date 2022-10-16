#pragma once
#include "EngineMathConstants.h"
#include "EngineMathOperations.h"

class Quaternion
{
public:
	Quaternion() : x(0), y(0), z(0), w(1)
	{
		
	}

	Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{
		
	}

	Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w)
	{
		
	}

	~Quaternion()
	{
		
	}

public:
	Quaternion operator +(const Quaternion& q) const
	{
		return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	Quaternion operator -(const Quaternion& q) const
	{
		return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
	}
	Quaternion operator *(const Quaternion& q) const
	{
		Quaternion quat;
		quat.x = (w * q.x - x * q.w - y * q.z - z * q.y);
		quat.y = (w * q.y - x * q.z - y * q.w - z * q.x);
		quat.z = (w * q.z - x * q.y - y * q.x - z * q.w);
		quat.w = (w * q.w - x * q.x - y * q.y - z * q.z);
		return quat;
	}
	Quaternion operator *(const float& scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
	}

public:
	static Vector3D ToEuler(const Quaternion& q)
	{
		const float test = q.x * q.y + q.z * q.w;
		constexpr float threshold = 0.4999995f;

		const float sqX = q.x * q.x;
		const float sqY = q.y * q.y;
		const float sqZ = q.z * q.z;
		const float sqW = q.w * q.w;

		float unit = sqX + sqY + sqZ + sqW;

		const float YawY = 2 * q.y * q.w - 2 * q.x * q.z;
		const float YawX = sqX - sqY - sqZ + sqW;

		const float RollY = 2 * q.x * q.w - 2 * q.y * q.z;
		const float RollX = -sqX + sqY - sqZ + sqW;

		float Yaw, Roll, Pitch;

		if (test > threshold * unit)
		{
			Pitch = (2.0f * std::atan2f(q.x, q.w) * RAD_TO_DEG);
			Yaw = -90.0f;
			Roll = 0;
		}
		else if (test < -threshold * unit)
		{
			Pitch = (-2.0f * std::atan2f(q.x, q.w) * RAD_TO_DEG);
			Yaw = 90.0f;
			Roll = 0;
		}
		else
		{
			Pitch = std::atan2f(YawY, YawX) * RAD_TO_DEG;
			Yaw = std::asinf(2.0f * test / unit) * RAD_TO_DEG;
			Roll = std::atan2f(RollY, RollX) * RAD_TO_DEG;
		}

		return Vector3D(Pitch, Yaw, Roll);
	}

	static Quaternion FromEuler(const Vector3D& euler)
	{
		constexpr float RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.0f;

		Vector3D e = Vector3D(euler);
		e.x = EngineMathOperations::FMod(euler.x, 360.0f) * RADS_DIVIDED_BY_2;
		e.y = EngineMathOperations::FMod(euler.y, 360.0f) * RADS_DIVIDED_BY_2;
		e.z = EngineMathOperations::FMod(euler.z, 360.0f) * RADS_DIVIDED_BY_2;

		const float sr = std::sinf(e.x); // Pitch
		const float cr = std::cosf(e.x); // Pitch
		const float sp = std::sinf(e.y); // Yaw
		const float cp = std::cosf(e.y); // Yaw
		const float sy = std::sinf(e.z); // Roll
		const float cy = std::cosf(e.z); // Roll

		Quaternion q;
		q.x = cr * sp * sy - sr * cp * cy;
		q.y = cr * sp * cy - sr * cp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		q.w = cr * cp * cy + sr * sp * sy;

		return q;
	}

public:
	void Normalize()
	{
		const float mag = std::sqrtf(x * x + y * y + z * z + w * w);
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}

	Quaternion Normalized() const
	{
		Quaternion q = Quaternion(*this);
		q.Normalize();
		return q;
	}

public:
	float x, y, z, w;
};
