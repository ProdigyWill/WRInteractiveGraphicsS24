#pragma once
#include "IAnimation.h"
#include "GraphicsObject.h"
#include <math.h> 

class MoveAnimation : public IAnimation
{
private:
	bool isMoving = false;
	bool isUpdated = false;
	glm::vec3 direction;
	float distanceToMove;
	float distanceMoved = 0;
	float speed;
	unsigned int emptyPosition;
	int emptyDiff;

public:
	MoveAnimation(glm::vec3 direction = {0, 0, 0}, float distanceToMove = 5.0f, float speed = 5)
		: IAnimation(), direction(direction), distanceToMove(distanceToMove), speed(speed) {}
	inline void ChangeState() { isMoving = !isMoving; }
	void UpdateDirection();
	bool CanMove();
	inline bool GetIsUpdated() { return isUpdated; }
	void SwapIsUpdated() { isUpdated = !isUpdated; }
	inline unsigned int GetEmptyPosition() { return emptyPosition; };
	inline void UpdateEmptyPosition(unsigned int emptyPosition) { this->emptyPosition = emptyPosition; }
	void Update(double elapsedSeconds);
};

