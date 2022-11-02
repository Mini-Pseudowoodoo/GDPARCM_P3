#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

#include "ImGui\\imgui.h"
#include "ImGui\\imgui_impl_win32.h"
#include "ImGui\\imgui_impl_dx11.h"

class IMObjectProperty
{
public:
	IMObjectProperty();
	~IMObjectProperty();

public:
	void Initialize(HWND hwnd);
	void Render();
};