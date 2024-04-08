#pragma once
#include "BaseObject.h"
#include <memory>

class GraphicsObject;

class IBehavior : public BaseObject
{
protected:
	std::shared_ptr<GraphicsObject> object;

public:
	IBehavior() : object(nullptr) {}
	virtual ~IBehavior() = default;

	virtual void SetObject(std::shared_ptr<GraphicsObject> object);
	virtual void Update(double elapsedSeconds) = 0;
};

