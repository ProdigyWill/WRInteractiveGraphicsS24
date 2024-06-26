#pragma once
#include "IAnimation.h"
#include "GraphicsObject.h"
#include <math.h> 

class MoveAnimation : public IAnimation
{
private:
	//If the object has completed moving
	bool isUpdated = false;

	bool isMoving = false;
	bool moveLock = false;
	glm::vec3 direction;
	float distanceToMove;
	float distanceMoved = 0;
	float speed;
	unsigned int emptyPosition = 0;
	int emptyDiff = 0;

public:
	MoveAnimation(glm::vec3 direction = {0, 0, 0}, float distanceToMove = 5.0f, float speed = 20.0f)
		: IAnimation(), direction(direction), distanceToMove(distanceToMove), speed(speed) {}
	inline void ChangeState() { isMoving = !isMoving; }
	void UpdateDirection();
	bool CanMove();
	inline bool GetIsMoving() { return isMoving; }
	inline bool GetIsUpdated() { return isUpdated; }
	inline bool GetMoveLock() { return moveLock; }
	void SwapIsUpdated() { isUpdated = !isUpdated; }
	inline unsigned int GetEmptyPosition() { return emptyPosition; };
	inline void UpdateEmptyPosition(unsigned int emptyPosition) { this->emptyPosition = emptyPosition; }
	void Update(double elapsedSeconds);
};

