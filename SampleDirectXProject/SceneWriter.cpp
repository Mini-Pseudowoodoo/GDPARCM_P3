#include "SceneWriter.h"
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "SimpleMath.h"

using namespace DirectX;

#include <json/json.h>
#include <json/value.h>

typedef std::fstream FileWriter;
SceneWriter::SceneWriter(std::string _directory)
{
	this->directory = _directory;
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::WriteToFile()
{
	std::string fileDir = this->directory + ".level";
	if (this->directory.find(".level") != std::string::npos) {
		fileDir = this->directory;
	}

	FileWriter sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	/*std::cout << "Selected filename " << fileDir << "\n";

	auto allObjects = GameObjectManager::Get()->GetGameObjectList();

	for (int i = 0; i < allObjects.size(); i++) {
		sceneFile << allObjects[i]->GetName() << std::endl;
		SimpleMath::Vector3 position = allObjects[i]->GetTransform()->GetPosition();
		SimpleMath::Vector3 rotation = allObjects[i]->GetTransform()->GetEulerAngles();
		SimpleMath::Vector3 scale = allObjects[i]->GetTransform()->GetScale();

		sceneFile << "Type: " << allObjects[i]->GetObjectType() << std::endl;
		sceneFile << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
		sceneFile << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
		sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;
		sceneFile << "HasPhysics: " << (bool)allObjects[i]->GetComponent<PhysicsComponent>() << std::endl;
	}*/

	Json::Value root;
	Json::StreamWriterBuilder builder;
	const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	auto allObjects = GameObjectManager::Get()->GetGameObjectList();

	for (int i = 0; i < allObjects.size(); i++) {
		SimpleMath::Vector3 position = allObjects[i]->GetTransform()->GetPosition();
		SimpleMath::Vector3 rotation = allObjects[i]->GetTransform()->GetEulerAngles();
		SimpleMath::Vector3 scale = allObjects[i]->GetTransform()->GetScale();

		const auto name = allObjects[i]->GetName();

		root[name]["type"] = allObjects[i]->GetObjectType();

		root[name]["position"]["x"] = position.x;
		root[name]["position"]["y"] = position.y;
		root[name]["position"]["z"] = position.z;

		root[name]["rotation"]["x"] = rotation.x;
		root[name]["rotation"]["y"] = rotation.y;
		root[name]["rotation"]["z"] = rotation.z;

		root[name]["scale"]["x"] = scale.x;
		root[name]["scale"]["y"] = scale.y;
		root[name]["scale"]["z"] = scale.z;

		root[name]["hasPhysics"] = (bool)allObjects[i]->GetComponent<PhysicsComponent>();
	}
	writer->write(root, &std::cout);
	sceneFile << root;

	sceneFile.close();
}
