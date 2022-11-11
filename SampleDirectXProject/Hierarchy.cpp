#include "Hierarchy.h"

Hierarchy::Hierarchy() : UIScreen("Hierarchy", true)
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::DrawUI()
{
	// Create ImGui Window;
	ImGui::Begin("Hierarchy", &isActive);

	vector<GameObject*> rootObjs = GameObjectManager::Get()->GetRoots();

	if (ImGui::TreeNode("Scene"))
	{
		for (int i = 0; i < rootObjs.size(); i++)
		{
			GameObject* obj = rootObjs[i];
			SetupNode(obj);
		}
		ImGui::TreePop();
	}

	ImGui::End();
}

void Hierarchy::SetupNode(GameObject* obj)
{
	vector<GameObject*> children = obj->GetChildren();
	if (children.size() > 0)
	{
		if (ImGui::TreeNode(obj->GetName().c_str()))
		{
			for (int i = 0; i < children.size(); i++)
			{
				SetupNode(children[i]);
				//ImGui::BulletText(children[j]->GetName().c_str());
			}
			ImGui::TreePop();
		}
	}
	else
	{
		ImGui::BulletText(obj->GetName().c_str());
	}
}

