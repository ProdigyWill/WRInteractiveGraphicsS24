#pragma once
#include <unordered_map>
#include <memory>
#include "GraphicsObject.h"
class ObjectManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectsMap;

public:
    void SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object);
    inline std::shared_ptr<GraphicsObject> GetObject(std::string& name) { return objectsMap[name]; };
    void Update(double elapsedSeconds);
};

