#pragma once
#include <unordered_map>
#include <memory>
#include "GraphicsObject.h"

class ObjectManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectsMap;
    unsigned int emptyPosition = 9;

public:
    bool CheckAnimation();
    bool CheckIfSolved();
    inline void SetEmptyPosition(unsigned int pos) { emptyPosition = pos; }
    inline unsigned int GetEmptyPosition() { return emptyPosition; }
    void SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object);
    inline std::shared_ptr<GraphicsObject> GetObject(std::string name) { return objectsMap[name]; };
    void Update(double elapsedSeconds);
    void SetBehaviorDefaults();
};

