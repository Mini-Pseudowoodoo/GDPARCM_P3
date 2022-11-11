#include "ObjectProperty.h"

ObjectProperty::ObjectProperty() : UIScreen("ObjectProperty", true)
{
	selectedObj = nullptr;
	pos = 0;
	rot = 0;
	scale = 0;
}

ObjectProperty::~ObjectProperty()
{
}

void ObjectProperty::DrawUI()
{
	// Create ImGui Window;
	ImGui::Begin("Object Property");

	String objName;
	if (selectedObj == nullptr)
		objName = "N/A";
	else
		objName = selectedObj->GetName();

	String selectedObjTxt = "Selected Object: " + objName;
	ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != nullptr)
	{
		// Object Transform
		TransformComponent* objTransform = selectedObj->GetTransform();

		// Position
		Vector3 origPos = objTransform->GetPosition();
		pos = new float[3] { origPos.x, origPos.y, origPos.z };
		ImGui::DragFloat3("Position", pos, 0.1f, 0.0f, 0.0f);
		objTransform->SetPosition(Vector3(pos[0], pos[1], pos[2]));

		if (ImGui::IsItemClicked(0) || (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()))
		{
			InputSystem::get()->ConsumeLeftMouseButton();
		}

		Vector3 origRot = objTransform->GetEulerAngles() * RAD_TO_DEG;
		rot = new float[3] { origRot.x, origRot.y, origRot.z };
		ImGui::DragFloat3("Rotation", rot, 0.1f, -360.0f, 360.0f);
		//objTransform->SetRotation(Quaternion(rot[0], rot[1], rot[2], 1.0f));
		objTransform->SetEulerAngles(Vector3(rot[0], rot[1], rot[2]) * DEG_TO_RAD);

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
