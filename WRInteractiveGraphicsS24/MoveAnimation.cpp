#include "MoveAnimation.h"

void MoveAnimation::UpdateDirection() {
	int pos = object->GetBoardPosition();
	if (pos + 3 == emptyPosition) { direction = { 0, -1, 0 }; emptyDiff = 3;  return; }
	if (pos - 3 == emptyPosition) { direction = { 0, 1, 0 }; emptyDiff = -3; return; }
	if (pos % 3 == 1) {
		if (pos + 1 == emptyPosition) { direction = { 1, 0, 0 }; emptyDiff = 1; return; }
	}
	else if (pos % 3 == 2) {
		if (pos - 1 == emptyPosition) { direction = { -1, 0, 0 }; emptyDiff = -1; return; }
		if (pos + 1 == emptyPosition) { direction = { 1, 0, 0 }; emptyDiff = 1; return; }
	}
	else {
		if (pos - 1 == emptyPosition) { direction = { -1, 0, 0 }; emptyDiff = -1; return; }
	}
}

bool MoveAnimation::CanMove() {
	int pos = object->GetBoardPosition();
	if (emptyPosition == 1) {
		return pos == 2 || pos == 4;
	}
	if (emptyPosition == 2) {
		return pos == 1 || pos == 3 || pos == 5;
	}
	if (emptyPosition == 3) {
		return pos == 2 || pos == 6;
	}
	if (emptyPosition == 4) {
		return pos == 1 || pos == 5 || pos == 7;
	}
	if (emptyPosition == 5) {
		return pos == 2 || pos == 4 || pos == 6 || pos == 8;
	}
	if (emptyPosition == 6) {
		return pos == 3 || pos == 5 || pos == 9;
	}
	if (emptyPosition == 7) {
		return pos == 4 || pos == 8;
	}
	if (emptyPosition == 8) {
		return pos == 5 || pos == 7 || pos == 9;
	}
	if (emptyPosition == 9) {
		return pos == 6 || pos == 8;
	}
}

void MoveAnimation::Update(double elapsedSeconds)
{
	if (object == nullptr) return;
	if (distanceMoved >= distanceToMove) {
		auto& frame = object->GetLocalReferenceFrame();
		glm::vec3 pos = frame[3];
		frame[3].x = round(frame[3].x);
		frame[3].y = round(frame[3].y);
		distanceMoved = 0;
		isMoving = false;
		moveLock = false;
		emptyPosition -= emptyDiff;
		object->SetBoardPosition(object->GetBoardPosition() + emptyDiff);
		isUpdated = true;
		return;
	}
	if (isMoving && CanMove()) {
		moveLock = true;
		UpdateDirection();
		float deltaSpeed = static_cast<float>(speed * elapsedSeconds);
		auto& frame = object->GetLocalReferenceFrame();
		glm::vec3 pos = frame[3];
		pos += direction * deltaSpeed;
		frame[3].x = pos.x;
		frame[3].y = pos.y;
		frame[3].z = pos.z;
		distanceMoved += deltaSpeed;
	}
}
