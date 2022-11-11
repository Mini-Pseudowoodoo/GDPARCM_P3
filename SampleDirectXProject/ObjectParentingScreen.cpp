#include "ObjectParentingScreen.h"

ObjectParentingScreen::ObjectParentingScreen() : UIScreen("ObjectParenting", true)
{
}

ObjectParentingScreen::~ObjectParentingScreen()
{
}

void ObjectParentingScreen::DrawUI()
{
	const GameObject* const& selectedObj = GameObjectManager::Get()->GetSelectedGameObject();

	ImGui::Begin("Object Parenting");
	String selectedObjName;
	if (selectedObj == nullptr)
		selectedObjName = "N/A";
	else
		selectedObjName = selectedObj->GetName();

	String selectedObjTxt = "Selected Object: " + selectedObjName;
	ImGui::Text(selectedObjTxt.c_str());

	if (selectedObj != nullptr)
	{
		unordered_map<char*, GameObject*> rootObjMap;
		static const char* currentRootObj;

		vector<GameObject*> rootObjVec = GameObjectManager::Get()->GetRoots();

		for (int i = 0; i < rootObjVec.size(); i++)
		{
			GameObject* obj = rootObjVec[i];
			//rootObjMap.emplace(obj->GetName().c_str(), obj);
		}

		// Display root parent objects
		if (ImGui::BeginCombo("Select Parent", currentRootObj))
		{
			/*map<char*, GameObject*>::iterator iterator;
			if (iterator != rootObjMap.end())
			{
				for (iterator = rootObjMap.begin(); iterator != rootObjMap.end(); iterator++)
				{
					bool isSelected = currentRootObj == iterator->first;
					
					if (ImGui::Selectable(iterator->first, isSelected))
						currentRootObj = iterator->first;

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
			}*/
			ImGui::EndCombo();
		}
		

		for (int i = 0; i < selectedParentList.size(); i++)
		{

		}
		String objToParentName;
		if (!selectedParentList.empty())
		{
			objToParentName = selectedParentList.back()->GetName();
		}
		else
		{
			objToParentName = "N/A";
		}
		String selectedObjTxt = "Object To Parent: " + objToParentName;
		ImGui::Text(selectedObjTxt.c_str());

		if (!selectedParentList.empty() && ImGui::Button("Set Parent"))
		{
			// Set Parent
		}
	}

	

	ImGui::End();
}

void ObjectParentingScreen::CreateComboObj(GameObject* obj)
{
}
