#include "IMObjectProperty.h"
#include "InputSystem.h"
#include <iostream>

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
		Vector3 origPos = objTransform->GetPosition();
		static float pos[3] = { origPos.x, origPos.y,  origPos.z };
		ImGui::DragFloat3("Position", pos, 0.05f, -10.0f, 10.0f);
		objTransform->SetPosition(Vector3(pos[0], pos[1], pos[2]));

		Quaternion origRot = objTransform->GetRotation();
		static float rot[3] = { origRot.x, origRot.y, origRot.z };
		ImGui::DragFloat3("Rotation", rot, 0.01f, -1.0f, 1.0f);
		objTransform->SetRotation(Quaternion(rot[0], rot[1], rot[2], 1.0f));

		Vector3 origScale = objTransform->GetScale();
		static float scale[3] = { origScale.x, origScale.y, origScale.z };
		ImGui::DragFloat3("Scale", scale, 0.05f, 0.0f, 10.0f);
		objTransform->SetScale(Vector3(scale[0], scale[1], scale[2]));

		if (ImGui::IsItemClicked(0))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}
	}
	
	ImGui::End();
	// Assemble Draw Data
	ImGui::Render();
	// Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
}