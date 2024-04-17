#pragma once
#include "IBehavior.h"
#include "GraphicsStructures.h"
#include "GraphicsObject.h"

class HighlightBehavior : public IBehavior
{
protected:
	HighlightParams params;
	float ambientIntensity = 0.0f;
public:
	void StoreDefaults() override;
	void SetParameter(IParams& param) override;
	void Update(double elapsedSeconds) override;
};

