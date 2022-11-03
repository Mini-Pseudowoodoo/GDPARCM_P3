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

void IMObjectProperty::Render(GameObject* selectedObj)
{
	// Start Dear ImGui Frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// Create ImGui Window;
	ImGui::Begin("Object Property");

	string objName;
	if (selectedObj == NULL)
		objName = "N/A";
	else
		objName = selectedObj->GetName();

	string selectedObjTxt = "Selected Object: " + objName;
	ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != NULL)
	{
		// Object Transform
		TransformComponent* objTransform = selectedObj->GetTransform();

		// Position
		Vector3 objPos = objTransform->GetPosition();
		static float pos[3] = { objPos.x, objPos.y,  objPos.z };
		ImGui::DragFloat3("Position", pos, 0.1f, -10.0f, 10.0f);
		objTransform->SetPosition(Vector3(pos[0], pos[1], pos[2]));
	}
	
	ImGui::End();
	// Assemble Draw Data
	ImGui::Render();
	// Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
}