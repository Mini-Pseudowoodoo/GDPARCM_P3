#include "ObjectParentingScreen.h"

ObjectParentingScreen::ObjectParentingScreen() : UIScreen("ObjectParenting", true)
{
}

ObjectParentingScreen::~ObjectParentingScreen()
{
}

void ObjectParentingScreen::DrawUI()
{
	GameObject* selectedObj = GameObjectManager::Get()->GetSelectedGameObject();

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
		static String objToParentName = "";
		
		unordered_map<String, GameObject*> gameObjsMap;
		vector<GameObject*> gameObjList = GameObjectManager::Get()->GetGameObjectList();

		for (int i = 0; i < gameObjList.size(); i++)
		{
			GameObject* obj = gameObjList[i];
			// Continue if same object
			if (selectedObj == obj) continue; 
			
			gameObjsMap.emplace(obj->GetName(), gameObjList[i]);
		}

		// Display root parent objects
		if (ImGui::BeginCombo("Select Parent", objToParentName.c_str()))
		{
			for (pair<String, GameObject*> it : gameObjsMap)
			{
				//static const char* select = it.first.c_str();
				bool isSelected = objToParentName == it.first.c_str();

				if (ImGui::Selectable(it.first.c_str(), isSelected))
				{
					objToParentName = it.first;
				}
					
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}
		
		//ImGui::Text("Object To Parent: " + (objToParentName == nullptr) ? objToParentName : "N/A");

		if (ImGui::Button("Set Parent"))
		{
			cout << objToParentName << endl;
			// Set Parent
			selectedObj->SetParent(gameObjsMap[objToParentName]);
		}
		if (selectedObj->GetParent() != nullptr)
		{
			if (ImGui::Button("Detach from Parent"))
			{
				selectedObj->RemoveFromParent();
			}
		}
	}

	

	ImGui::End();
}

void ObjectParentingScreen::CreateComboObj(GameObject* obj)
{
}
