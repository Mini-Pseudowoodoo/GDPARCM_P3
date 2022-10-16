#pragma once

#include <vector>

#include "Window.h"
#include "InputListener.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

class GameObject;
class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow() override;

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	static AppWindow* sharedInstance;

	static AppWindow* getInstance();

	static void initialize();

	void update();

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point& delta_mouse) override;
	void onLeftMouseButtonDown(const Point& mouse_pos) override;
	void onLeftMouseButtonUp(const Point& mouse_pos) override;
	void onRightMouseButtonDown(const Point& mouse_pos) override;
	void onRightMouseButtonUp(const Point& mouse_pos) override;
private:
	SwapChain * m_swap_chain;
	/*VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;*/
	//ConstantBuffer* m_cb;

public:
	Matrix4x4 GetViewMatrix() const;
	Matrix4x4 GetProjectionMatrix() const;

private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	bool m_rmb_down = false;

	float m_up = 0.0f;
	float m_forward = 0.0f;
	float m_right = 0.0f;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_matrix;
	Matrix4x4 m_projection_matrix;
	GameObject* gameObject_0 = nullptr;
	GameObject* gameObject_1 = nullptr;
	GameObject* gameObject_2 = nullptr;
	std::vector<GameObject*> gameObjects;
};

