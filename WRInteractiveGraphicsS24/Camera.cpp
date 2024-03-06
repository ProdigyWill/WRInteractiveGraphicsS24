#include "Camera.h"

void Camera::SetLookFrame(glm::mat4 lookFrame)
{
	this->lookFrame = lookFrame;
}

void Camera::SetSpeed(int speed)
{
	this->speed = speed;
}

void Camera::SetPosition(glm::vec3 pos)
{
	referenceFrame[3] = { pos, 1.0f };
}

glm::mat4 Camera::LookForward()
{
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraForward = -lookFrame[2];
	glm::vec3 cameraTarget = cameraPosition + cameraForward;
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

glm::mat4 Camera::LookAt(const glm::vec3& point)
{
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, point, cameraUp);
}

void Camera::MoveForward(double elapsedSeconds)
{
	glm::vec3 forward = -lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	forward = forward * static_cast<float>(10.0f * elapsedSeconds);
	position = position + forward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveBackward(double elapsedSeconds)
{
	glm::vec3 backward = lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	backward = backward * static_cast<float>(10.0f * elapsedSeconds);
	position = position + backward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveLeft(double elapsedSeconds)
{
	glm::vec3 toLeft = -lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	toLeft = toLeft * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toLeft;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveRight(double elapsedSeconds)
{
	glm::vec3 toRight = lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	toRight = toRight * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toRight;
	referenceFrame[3] = glm::vec4(position, 1.0f);;
}

void Camera::MoveUp(double elapsedSeconds)
{
	glm::vec3 toUp = referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	toUp = toUp * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toUp;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveDown(double elapsedSeconds)
{
	glm::vec3 toDown = -referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	toDown = toDown * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toDown;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::LookLeft(double elapsedSeconds)
{
	glm::vec3 yAxis = referenceFrame[1];
	float rotationAngle = static_cast<float>(elapsedSeconds);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, yAxis);
	lookFrame *= rotationMatrix;
}

void Camera::LookRight(double elapsedSeconds)
{
	glm::vec3 yAxis = referenceFrame[1];
	float rotationAngle = -static_cast<float>(elapsedSeconds);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, yAxis);
	lookFrame *= rotationMatrix;
}

void Camera::LookUp(double elapsedSeconds)
{
	glm::vec3 xAxis = referenceFrame[0];
	float rotationAngle = static_cast<float>(elapsedSeconds);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, xAxis);
	lookFrame *= rotationMatrix;
}

void Camera::LookDown(double elapsedSeconds)
{
	glm::vec3 xAxis = referenceFrame[0];
	float rotationAngle = -static_cast<float>(elapsedSeconds);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, xAxis);
	lookFrame *= rotationMatrix;
}
