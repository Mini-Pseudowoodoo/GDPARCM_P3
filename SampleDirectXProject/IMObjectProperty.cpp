#include "IMObjectProperty.h"

IMObjectProperty::IMObjectProperty()
{
}

IMObjectProperty::~IMObjectProperty()
{
}

void IMObjectProperty::Initialize(HWND hwnd)
{
	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);

	ID3D11Device* device = GraphicsEngine::get()->getRenderSystem()->getDevice();
	ID3D11DeviceContext* deviceContext = GraphicsEngine::get()->getRenderSystem()->getID3D11DeviceContext();
	
	ImGui_ImplDX11_Init(device, deviceContext);
	ImGui::StyleColorsDark();
}

void IMObjectProperty::Render()
{
	// Start Dear ImGui Frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// Create ImGui Window;
	ImGui::Begin("Object Property");
	ImGui::End();
	// Assemble Draw Data
	ImGui::Render();
	// Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

