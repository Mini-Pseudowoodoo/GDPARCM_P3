#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class GameObject;
class GameObjectManager
{
private:
	static GameObjectManager* instance;

public:
	static void Initialize();
	static GameObjectManager* Get();

public:
	void Update();

public:
	void CreateGameObject();
	void CreateCube();
	void CreatePlane();
	void CreateTeapot();
	void CreateBunny();
	void CreateArmadillo();

public:
	void SelectGameObject(GameObject* inObj);
	GameObject* GetSelectedGameObject() const;

public:
	const std::vector<GameObject*>& GetGameObjectList() const;
	const std::vector<GameObject*> GetRoots() const;

private:
	std::vector<GameObject*> gameObjectList;
	std::unordered_map<std::string, GameObject*> gameObjectMap;
	GameObject* selectedObj;

private:
	const std::string NAME_CUBE = "Cube";
	const std::string NAME_PLANE = "Plane";
	const std::string NAME_TEAPOT = "Teapot";
	const std::string NAME_BUNNY = "Bunny";
	const std::string NAME_ARMADILLO = "Armadillo";
};

