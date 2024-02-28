#include "ObjectManager.h"

void ObjectManager::SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	objectsMap[name] = object;
}

void ObjectManager::Update(double elapsedSeconds)
{
	for (const auto& pair : objectsMap) {
		pair.second->Update(elapsedSeconds);
	}
}

