#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
class Camera
{
protected:
	glm::mat4 referenceFrame = glm::mat4(1.0f);
	glm::mat4 lookFrame;
	int speed = 10;
public:
	void SetLookFrame(glm::mat4 lookFrame);
	void SetSpeed(int speed);
	void SetPosition(glm::vec3 pos);
	glm::mat4 LookForward();
	glm::mat4 LookAt(const glm::vec3& point);
	void MoveForward(double elapsedSeconds);
	void MoveBackward(double elapsedSeconds);
	void MoveLeft(double elapsedSeconds);
	void MoveRight(double elapsedSeconds);
	void MoveUp(double elapsedSeconds);
	void MoveDown(double elapsedSeconds);
	void LookLeft(double elapsedSeconds);
	void LookRight(double elapsedSeconds);
	void LookUp(double elapsedSeconds);
	void LookDown(double elapsedSeconds);
};

