#include "SceneWriter.h"
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameObjectManager.h"
#include "SimpleMath.h"

using namespace DirectX;

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
	std::string fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != std::string::npos) {
		fileDir = this->directory;
	}

	FileWriter sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

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
	}

	sceneFile.close();
}
