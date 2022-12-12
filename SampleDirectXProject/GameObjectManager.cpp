#include "GameObjectManager.h"
#include "GameObject.h"
#include "EngineTime.h"

#include "MeshComponent.h"

#include "GraphicsEngine.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{
    this->physicsCommon = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
    this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

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
    const float delta = EngineTime::getDeltaTime();

    if (delta > 0.0f)
    {
        if (EngineBackend::Get()->GetMode() == EditorMode::PLAY)
            physicsWorld->update(delta);
        for (const auto& gameObject : gameObjectList)
        {
            gameObject->Update(delta);
        }
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

    if (TransformComponent* transform = cube->GetTransform())
    {
        float rand = std::rand() % 5;
        //transform->SetPosition({ rand, 5, rand });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\box.obj");
    Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    
    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        cube->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        meshComponent->SetTexture(texture);
    }

    PhysicsComponent* phys = new PhysicsComponent();
    cube->AttachComponent(phys);

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

void GameObjectManager::CreateCubes(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        CreateCube();
    }
}

void GameObjectManager::CreatePlane()
{
    GameObject* cube = GameObject::Instantiate(NAME_PLANE);

    if (TransformComponent* transform = cube->GetTransform())
    {
        transform->SetScale({ 5, 0.1f, 5 });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\box.obj");
    Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");

    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        cube->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        meshComponent->SetTexture(texture);
    }

    PhysicsComponent* phys = new PhysicsComponent();
    cube->AttachComponent(phys);
    phys->GetRigidbody()->setType(BodyType::KINEMATIC);

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

void GameObjectManager::CreateTeapot()
{
    GameObject* obj = GameObject::Instantiate(NAME_TEAPOT);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj");
    Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_TEAPOT) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_TEAPOT + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateBunny()
{
    GameObject* obj = GameObject::Instantiate(NAME_BUNNY);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\bunny.obj");
    Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\ground.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_BUNNY) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_BUNNY + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateArmadillo()
{
    GameObject* obj = GameObject::Instantiate(NAME_ARMADILLO);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
    Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_ARMADILLO) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_ARMADILLO + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateObjectFromFile(std::string name, PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale)
{
    switch (type)
    {
    case PrimitiveType::CUBE:
        break;
    case PrimitiveType::SPHERE:
        break;
    case PrimitiveType::PLANE:
        break;
    case PrimitiveType::CAPSULE:
        break;
    }
}

void GameObjectManager::SaveEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->SaveEditState();
    }
}

void GameObjectManager::RestoreEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->RestoreEditState();
    }
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

PhysicsWorld* GameObjectManager::GetPhysicsWorld()
{
    return physicsWorld;
}

PhysicsCommon* GameObjectManager::GetPhysicsCommon()
{
    return physicsCommon;
}
