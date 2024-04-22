#include "ObjectManager.h"
#include "MoveAnimation.h"

void ObjectManager::SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	objectsMap[name] = object;
}

void ObjectManager::Update(double elapsedSeconds)
{
	for (const auto& pair : objectsMap) {
		pair.second->Update(elapsedSeconds);
        std::shared_ptr<MoveAnimation> animation = std::static_pointer_cast<MoveAnimation>(pair.second->GetAnimation());
        if (animation) {
            if (animation->GetIsUpdated()) {
                emptyPosition = animation->GetEmptyPosition();
                animation->SwapIsUpdated();
            }
        }
	}
}

void ObjectManager::SetBehaviorDefaults() {
    for (const auto& objectPair : objectsMap) {
        auto& graphicsObject = objectPair.second;

        if (graphicsObject) {
            graphicsObject->SetBehaviorDefaults();
        }
    }
}

