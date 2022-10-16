#pragma once
#include <memory>

#include "Vector3D.h"
#include "Vector4D.h"
#include "Quaternion.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{

	}
	~Matrix4x4()
	{

	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);

		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& vector)
	{
		m_mat[3][0] = vector.x;
		m_mat[3][1] = vector.y;
		m_mat[3][2] = vector.z;
	}

	void setRotationX(const float& angle)
	{
		const float rad = angle * DEG_TO_RAD;
		m_mat[1][1] = cosf(rad);
		m_mat[1][2] = sinf(rad);
		m_mat[2][1] = -sinf(rad);
		m_mat[2][2] = cosf(rad);
	}

	void setRotationY(const float& angle)
	{
		const float rad = angle * DEG_TO_RAD;
		m_mat[0][0] = cosf(rad);
		m_mat[0][2] = -sinf(rad);
		m_mat[2][0] = sinf(rad);
		m_mat[2][2] = cosf(rad);
	}

	void setRotationZ(const float& angle)
	{
		const float rad = angle * DEG_TO_RAD;
		m_mat[0][0] = cosf(rad);
		m_mat[0][1] = sinf(rad);
		m_mat[1][0] = -sinf(rad);
		m_mat[1][1] = cosf(rad);
	}

	void setRotation(const Quaternion& quat)
	{
		const float x2 = quat.x + quat.x;		const float y2 = quat.y + quat.y;		const float z2 = quat.z + quat.z;
		const float xx = quat.x * x2;			const float xy = quat.x * y2;			const float xz = quat.x * z2;
		const float yy = quat.y * y2;			const float yz = quat.y * z2;			const float zz = quat.z * z2;
		const float wx = quat.w * x2;			const float wy = quat.w * y2;			const float wz = quat.w * z2;

		m_mat[0][0] = 1.0f - (yy + zz);	m_mat[1][0] = xy - wz;				m_mat[2][0] = xz + wy;			m_mat[3][0] = 0.0f;
		m_mat[0][1] = xy + wz;			m_mat[1][1] = 1.0f - (xx + zz);		m_mat[2][1] = yz - wx;			m_mat[3][1] = 0.0f;
		m_mat[0][2] = xz - wy;			m_mat[1][2] = yz + wx;				m_mat[2][2] = 1.0f - (xx + yy);	m_mat[3][2] = 0.0f;
		m_mat[0][3] = 0.0f;				m_mat[1][3] = 0.0f;					m_mat[2][3] = 0.0f;				m_mat[3][3] = 1.0f;
	}

	float getDeterminant()
	{
		Vector4D minor;

		Vector4D v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		Vector4D v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		Vector4D v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		float det = -(this->m_mat[0][3] * minor.x + this->m_mat[1][3] * minor.y + this->m_mat[2][3] * minor.z +
			this->m_mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->m_mat[j][0]);
					vec[a].y = (this->m_mat[j][1]);
					vec[a].z = (this->m_mat[j][2]);
					vec[a].w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = powf(-1.0f, i) * v.x / det;
			out.m_mat[1][i] = powf(-1.0f, i) * v.y / det;
			out.m_mat[2][i] = powf(-1.0f, i) * v.z / det;
			out.m_mat[3][i] = powf(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	void setScale(const Vector3D& vector)
	{
		m_mat[0][0] = vector.x;
		m_mat[1][1] = vector.y;
		m_mat[2][2] = vector.z;
	}

	Vector3D getZDirection() const
	{
		return {m_mat[2][0], m_mat[2][1], m_mat[2][2]};
	}
	Vector3D getYDirection() const
	{
		return { m_mat[1][0], m_mat[1][1], m_mat[1][2] };
	}
	Vector3D getXDirection() const
	{
		return {m_mat[0][0], m_mat[0][1], m_mat[0][2]};
	}
	Vector3D getTranslation() const
	{
		return {m_mat[3][0], m_mat[3][1], m_mat[3][2]};
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		const float rad = fov * DEG_TO_RAD;
		float yscale = 1.0f / tanf(rad / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();

		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

public:
	void operator *= (const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.m_mat[i][j] = 
					m_mat[i][0] * matrix.m_mat[0][j] + 
					m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] +
					m_mat[i][3] * matrix.m_mat[3][j];
			}
		}

		::memcpy(m_mat, out.m_mat, sizeof(float) * 16);
	}

public:
	float m_mat[4][4] = {};
};
