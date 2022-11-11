#include "GameObjectManager.h"
#include "GameObject.h"
#include "EngineTime.h"

#include "Cube.h"
#include "Plane.h"
#include "MeshComponent.h"

GameObjectManager* GameObjectManager::instance = nullptr;

void GameObjectManager::Initialize()
{
    instance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::Get()
{
    return instance;
}

void GameObjectManager::Update()
{
    for (const auto& gameObject : gameObjectList)
    {
        gameObject->Update(EngineTime::getDeltaTime());
    }
}

void GameObjectManager::CreateGameObject()
{
    GameObject* newObj = GameObject::Instantiate();
    gameObjectList.push_back(newObj);

    SelectGameObject(newObj);
}

void GameObjectManager::CreateCube()
{
    GameObject* cube = GameObject::Instantiate(NAME_CUBE);

    Cube* cubeMesh = new Cube();
    MeshComponent* cubeComponent = new MeshComponent();
    cube->AttachComponent(cubeComponent);
    cubeComponent->SetMesh(cubeMesh);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CUBE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        cube->SetName(NAME_CUBE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(cube);
    gameObjectMap.emplace(cube->GetName(), cube);
    SelectGameObject(cube);
}

void GameObjectManager::CreatePlane()
{
    GameObject* plane = GameObject::Instantiate(NAME_PLANE);

    PlaneMesh* planeMesh = new PlaneMesh();
    MeshComponent* planeComponent = new MeshComponent();
    plane->AttachComponent(planeComponent);
    planeComponent->SetMesh(planeMesh);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_PLANE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        plane->SetName(NAME_PLANE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(plane);
    gameObjectMap.emplace(plane->GetName(), plane);

    SelectGameObject(plane);
}

void GameObjectManager::SelectGameObject(GameObject* inObj)
{
    selectedObj = inObj;

    if (MeshComponent* mesh = selectedObj->GetComponent<MeshComponent>())
        mesh->SetOutlined(true);
}

GameObject* GameObjectManager::GetSelectedGameObject() const
{
    return selectedObj;
}

const std::vector<GameObject*>& GameObjectManager::GetGameObjectList() const
{
    return gameObjectList;
}

const std::vector<GameObject*> GameObjectManager::GetRoots() const
{
    std::vector<GameObject*> roots;

    for (const auto& gameObject : gameObjectList)
    {
        if (gameObject->IsRoot())
            roots.push_back(gameObject);
    }

    return roots;
}
