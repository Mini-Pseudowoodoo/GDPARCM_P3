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
		static const char* currentRootObj = NULL;
		unordered_map<const char*, GameObject*> rootObjMap;
		vector<GameObject*> rootObjVec = GameObjectManager::Get()->GetRoots();

		for (int i = 0; i < rootObjVec.size(); i++)
		{
			GameObject* obj = rootObjVec[i];
			// Continue if same object
			if (selectedObj == obj) continue; 
			
			rootObjMap.emplace(obj->GetName().c_str(), rootObjVec[i]);
		}

		// Display root parent objects
		if (ImGui::BeginCombo("Select Parent", currentRootObj))
		{
			for (pair<const char*, GameObject*> it : rootObjMap)
			{
				cout << (it.first == NULL) << endl;
				bool isSelected = currentRootObj == it.first;

				if (ImGui::Selectable(it.first, isSelected))
					currentRootObj = it.first;

				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

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
