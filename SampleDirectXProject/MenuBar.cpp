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
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Object Property"))
            {
                UIManager::Get()->ToggleUI("OBJECT_PROPERTY");
            }
            if (ImGui::MenuItem("Object Parenting"))
            {
                UIManager::Get()->ToggleUI("OBJECT_PARENTING");
            }
            if (ImGui::MenuItem("Hierarchy"))
            {
                UIManager::Get()->ToggleUI("HIERARCHY");
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
                if (ImGui::MenuItem("Cubes"))
                {
                    GameObjectManager::Get()->CreateCubes(10);
                }
                if (ImGui::MenuItem("Plane"))
                {
                    GameObjectManager::Get()->CreatePlane();
                }
                /*if (ImGui::MenuItem("Teapot"))
                {
                    GameObjectManager::Get()->CreateTeapot();
                }
                if (ImGui::MenuItem("Bunny"))
                {
                    GameObjectManager::Get()->CreateBunny();
                }
                if (ImGui::MenuItem("Armadillo"))
                {
                    GameObjectManager::Get()->CreateArmadillo();
                }*/

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About"))
        {
            if (ImGui::MenuItem("Credits"))
            {
                UIManager::Get()->ToggleUI("CREDITS_SCREEN");
            }
            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }
}
