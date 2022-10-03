#pragma once

class Quad
{
public:
	Quad();
	~Quad();

public:
	void Draw();

private:
	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class ConstantBuffer* m_cb;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;
};

