#include "MenuBar.h"
#include "GameObjectManager.h"

MenuBar::MenuBar() : UIScreen("MenuBar", true)
{
}

MenuBar::~MenuBar()
{
}

void MenuBar::DrawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Object Property"))
            {
                UIManager::Get()->ToggleUI("OBJECT_PROPERTY");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            if (ImGui::BeginMenu("Create GameObject"))
            {
                if (ImGui::MenuItem("Cube"))
                {
                    GameObjectManager::Get()->CreateCube();
                }
                if (ImGui::MenuItem("Plane"))
                {
                    GameObjectManager::Get()->CreatePlane();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits"))
            {

                //UIManager::Get()->ToggleUI("CREDITS_SCREEN");
            }
            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }
}
