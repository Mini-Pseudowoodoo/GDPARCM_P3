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
		::memset(m_mat, 0, sizeof(float) * 16);

		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
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

	void setRotation(const Quaternion& q)
	{
		float sqw = q.w * q.w;
		float sqx = q.x * q.x;
		float sqy = q.y * q.y;
		float sqz = q.z * q.z;

		float invs = 1.0f / (sqx + sqy + sqz + sqw);
		m_mat[0][0] = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
		m_mat[1][1] = (-sqx + sqy - sqz + sqw) * invs;
		m_mat[2][2] = (-sqx - sqy + sqz + sqw) * invs;

		float tmp1 = q.x * q.y;
		float tmp2 = q.z * q.w;
		m_mat[1][0] = 2.0f * (tmp1 + tmp2) * invs;
		m_mat[0][1] = 2.0f * (tmp1 - tmp2) * invs;

		tmp1 = q.x * q.z;
		tmp2 = q.y * q.w;
		m_mat[2][0] = 2.0f * (tmp1 - tmp2) * invs;
		m_mat[0][2] = 2.0f * (tmp1 + tmp2) * invs;
		tmp1 = q.y * q.z;
		tmp2 = q.x * q.w;
		m_mat[2][1] = 2.0f * (tmp1 + tmp2) * invs;
		m_mat[1][2] = 2.0f * (tmp1 - tmp2) * invs;
	}

	void SetRotation(const Vector3D& e)
	{
		Vector3D euler = e * DEG_TO_RAD;

		float ch = std::cosf(euler.x);
		float sh = std::sinf(euler.x);
		float ca = std::cosf(euler.y);
		float sa = std::sinf(euler.y);
		float cb = std::cosf(euler.z);
		float sb = std::sinf(euler.z);

		m_mat[0][0] = ch * ca;
		m_mat[0][1] = sh * sb - ch * sa * cb;
		m_mat[0][2] = ch * sa * sb + sh * cb;
		m_mat[1][0] = sa;
		m_mat[1][1] = ca * cb;
		m_mat[1][2] = -ca * sb;
		m_mat[2][0] = -sh * ca;
		m_mat[2][1] = sh * sa * cb + ch * sb;
		m_mat[2][2] = -sh * sa * sb + ch * cb;
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

			float i_f = (float)i;

			out.m_mat[0][i] = powf(-1.0f, i_f) * v.x / det;
			out.m_mat[1][i] = powf(-1.0f, i_f) * v.y / det;
			out.m_mat[2][i] = powf(-1.0f, i_f) * v.z / det;
			out.m_mat[3][i] = powf(-1.0f, i_f) * v.w / det;
		}

		this->setMatrix(out);
	}

	Matrix4x4 GetInverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) 
			return *this;
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

			float i_f = (float)i;

			out.m_mat[0][i] = powf(-1.0f, i_f) * v.x / det;
			out.m_mat[1][i] = powf(-1.0f, i_f) * v.y / det;
			out.m_mat[2][i] = powf(-1.0f, i_f) * v.z / det;
			out.m_mat[3][i] = powf(-1.0f, i_f) * v.w / det;
		}

		return out;
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

	Quaternion GetRotation() const
	{
		Quaternion q;

		float trace = m_mat[0][0] + m_mat[1][1] + m_mat[2][2];
		if (trace > 0) {
			float s = 0.5f / sqrtf(trace + 1.0f);
			q.w = 0.25f / s;
			q.x = (m_mat[2][1] - m_mat[1][2]) * s;
			q.y = (m_mat[0][2] - m_mat[2][0]) * s;
			q.z = (m_mat[1][0] - m_mat[0][1]) * s;
		}
		else {
			if (m_mat[0][0] > m_mat[1][1] && m_mat[0][0] > m_mat[2][2]) {
				float s = 2.0f * sqrtf(1.0f + m_mat[0][0] - m_mat[1][1] - m_mat[2][2]);
				q.w = (m_mat[2][1] - m_mat[1][2]) / s;
				q.x = 0.25f * s;
				q.y = (m_mat[0][1] + m_mat[1][0]) / s;
				q.z = (m_mat[0][2] + m_mat[2][0]) / s;
			}
			else if (m_mat[1][1] > m_mat[2][2]) {
				float s = 2.0f * sqrtf(1.0f + m_mat[1][1] - m_mat[0][0] - m_mat[2][2]);
				q.w = (m_mat[0][2] - m_mat[2][0]) / s;
				q.x = (m_mat[0][1] + m_mat[1][0]) / s;
				q.y = 0.25f * s;
				q.z = (m_mat[1][2] + m_mat[2][1]) / s;
			}
			else {
				float s = 2.0f * sqrtf(1.0f + m_mat[2][2] - m_mat[0][0] - m_mat[1][1]);
				q.w = (m_mat[1][0] - m_mat[0][1]) / s;
				q.x = (m_mat[0][2] + m_mat[2][0]) / s;
				q.y = (m_mat[1][2] + m_mat[2][1]) / s;
				q.z = 0.25f * s;
			}
		}

		return q;
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
	static Matrix4x4 Perspective(float fov, float aspect, float znear, float zfar)
	{
		Matrix4x4 out = Matrix4x4::identity;

		const float fovRad = fov * DEG_TO_RAD;
		const float yscale = 1.0f / tanf(fovRad / 2.0f);
		const float xscale = yscale / aspect;

		out.m_mat[0][0] = xscale;
		out.m_mat[1][1] = yscale;
		out.m_mat[2][2] = zfar / (zfar - znear);
		out.m_mat[2][3] = 1.0f;
		out.m_mat[3][2] = (-znear * zfar) / (zfar - znear);

		return out;
	}

	static Matrix4x4 Orthographic(float width, float height, float near_plane, float far_plane)
	{
		Matrix4x4 out = Matrix4x4::identity;

		out.m_mat[0][0] = 2.0f / width;
		out.m_mat[1][1] = 2.0f / height;
		out.m_mat[2][2] = 1.0f / (far_plane - near_plane);
		out.m_mat[3][2] = -(near_plane / (far_plane - near_plane));

		return out;
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

public:
	static const Matrix4x4 identity;
};
