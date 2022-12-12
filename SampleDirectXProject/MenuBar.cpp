#include "MenuBar.h"
#include "GameObjectManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

MenuBar::MenuBar() : UIScreen("MenuBar", true)
{
    openSceneDialog = new ImGui::FileBrowser();
    openSceneDialog->SetTitle("Open Scene");
    openSceneDialog->SetTypeFilters({ ".iet" });

    saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
    saveSceneDialog->SetTitle("Save Scene");
    saveSceneDialog->SetTypeFilters({ ".iet" });
}

MenuBar::~MenuBar()
{
    delete openSceneDialog;
    delete saveSceneDialog;
}

void MenuBar::DrawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {
                this->openSceneDialog->Open();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                this->saveSceneDialog->Open();
            }
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
                this->saveSceneDialog->Open();
            }
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

        this->openSceneDialog->Display();
        this->saveSceneDialog->Display();

        if (this->saveSceneDialog->HasSelected())
        {
            SceneWriter writer = SceneWriter(this->saveSceneDialog->GetSelected().string());
            writer.WriteToFile();

            this->saveSceneDialog->ClearSelected();
            this->saveSceneDialog->Close();
        }

        else if (this->openSceneDialog->HasSelected()) {
            SceneReader reader = SceneReader(this->openSceneDialog->GetSelected().string());
            reader.ReadFromFile();

            this->openSceneDialog->ClearSelected();
            this->openSceneDialog->Close();
        }
    }
}
