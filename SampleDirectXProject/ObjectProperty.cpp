#include "ObjectProperty.h"
#include "GameObjectManager.h"

ObjectProperty::ObjectProperty() : UIScreen("ObjectProperty", true)
{
	pos = 0;
	rot = 0;
	scale = 0;
}

ObjectProperty::~ObjectProperty()
{
}

void ObjectProperty::DrawUI()
{
	// Create ImGui Window
	ImGui::Begin("Object Property", &isActive);
	
	const GameObject* const& selectedObj = GameObjectManager::Get()->GetSelectedGameObject();
	String selectedObjTxt = "Selected Object: " + ((selectedObj == nullptr) ? "N/A" : selectedObj->GetName());
	ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != nullptr)
	{
		// Object Transform
		TransformComponent* objTransform = selectedObj->GetTransform();

		// Position
		Vector3 origPos = objTransform->GetPosition();
		pos = new float[3] { origPos.x, origPos.y, origPos.z != 0 ? -origPos.z : 0 };
		ImGui::DragFloat3("Position", pos, 0.1f, 0.0f, 0.0f);
		objTransform->SetPosition(Vector3(pos[0], pos[1], -pos[2]));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		Vector3 origRot = objTransform->GetEulerAngles() * RAD_TO_DEG;
		rot = new float[3] { origRot.x, origRot.y, origRot.z };
		ImGui::DragFloat3("Rotation", rot, 0.1f, -360.0f, 360.0f);
		objTransform->SetEulerAngles(Vector3(rot[0], rot[1], rot[2]) * DEG_TO_RAD);
		//objTransform->SetRotation(Quaternion(rot[0], rot[1], rot[2], 1.0f));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		Vector3 origScale = objTransform->GetScale();
		scale = new float[3] { origScale.x, origScale.y, origScale.z };
		ImGui::DragFloat3("Scale", scale, 0.1f, 0.0f, 0.0f);
		objTransform->SetScale(Vector3(scale[0], scale[1], scale[2]));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}
	}

	ImGui::End();
}
