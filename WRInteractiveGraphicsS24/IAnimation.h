#pragma once
#include "IBehavior.h"
#include <memory>

class GraphicsObject;

class IAnimation : public IBehavior
{
protected:
	std::shared_ptr<GraphicsObject> object;

public:
	IAnimation() : object(nullptr) {}
	virtual ~IAnimation() = default;

	virtual void SetObject(std::shared_ptr<GraphicsObject> object);
	virtual void Update(double elapsedSeconds) = 0;
};

