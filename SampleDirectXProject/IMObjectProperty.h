#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>

#include "ImGui\\imgui.h"
#include "ImGui\\imgui_impl_win32.h"
#include "ImGui\\imgui_impl_dx11.h"

using namespace std;

class IMObjectProperty
{
public:
	IMObjectProperty();
	~IMObjectProperty();

public:
	void Initialize(HWND hwnd);
	void Render(GameObject* selectedObj);

private:
	float* pos;
	float* rot;
	float* scale;
};