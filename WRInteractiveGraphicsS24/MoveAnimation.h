#pragma once
#include "IAnimation.h"
class MoveAnimation : public IAnimation
{
private:
	bool isMoving = false;
	glm::vec3 direction;
	float distanceToMove;
	float distanceMoved = 0;
	float speed;

public:
	MoveAnimation(glm::vec3 direction = {0, 0, -1}, float distanceToMove = 20, float speed = 5)
		: IAnimation(), direction(direction), distanceToMove(distanceToMove), speed(speed) {}
	inline void ChangeState() { isMoving = !isMoving; }
	void Update(double elapsedSeconds);
};

