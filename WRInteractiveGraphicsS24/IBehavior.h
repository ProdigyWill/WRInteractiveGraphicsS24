#pragma once
#include "BaseObject.h"
#include <memory>
#include "GraphicsStructures.h"

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
	virtual void SetParameter(IParams& params) {}
	virtual void StoreDefaults() {}
};

