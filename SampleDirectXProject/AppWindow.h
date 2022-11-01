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
class AppWindow: public Window
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

	static AppWindow* Get();

	static void Initialize();

	void update();
private:
	SwapChain * m_swap_chain;

private:
	GameObject* gameObject_0 = nullptr;
	GameObject* gameObject_1 = nullptr;
	GameObject* gameObject_2 = nullptr;
	std::vector<GameObject*> gameObjects;

	class SceneCamera* sceneCamera = nullptr;
};

