#include "GraphicsObject.h"
#include "IAnimation.h"
#include <glm/gtc/matrix_transform.hpp>

GraphicsObject::GraphicsObject() : referenceFrame(1.0f), parent(nullptr)
{
	material.ambientIntensity = 0.2f;
	material.specularIntensity = 0.5f;
	material.shininess = 32.0f;
}

GraphicsObject::~GraphicsObject()
{
}

const glm::mat4 GraphicsObject::GetReferenceFrame() const
{
	if (parent != nullptr) {
		return parent->referenceFrame * referenceFrame;
	}
	return referenceFrame;
}

void GraphicsObject::CreateVertexBuffer(unsigned int numberOfElementsPerVertex)
{
	buffer = std::make_shared<VertexBuffer>(numberOfElementsPerVertex);
}

void GraphicsObject::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	this->buffer = buffer;
}

void GraphicsObject::SetReferenceFrame(glm::mat4 referenceFrame)
{
	this->referenceFrame = referenceFrame;
}

void GraphicsObject::SetAnimation(std::shared_ptr<IAnimation> animation)
{
	this->animation = animation;
}

void GraphicsObject::StaticAllocateVertexBuffer()
{
	buffer->Select();
	buffer->StaticAllocate();
	buffer->Deselect();
	for (auto& child : children) {
		child->StaticAllocateVertexBuffer();
	}
}

void GraphicsObject::AddChild(std::shared_ptr<GraphicsObject> child)
{
	children.push_back(child);
	child->parent = this;
}

void GraphicsObject::SetPosition(const glm::vec3& position)
{
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void GraphicsObject::ResetOrientation()
{
	glm::vec4 position = referenceFrame[3];
	referenceFrame = glm::mat4(1.0f);
	referenceFrame[3] = position;
}

void GraphicsObject::RotateLocalX(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame,
		glm::radians(degrees),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);
}

void GraphicsObject::RotateLocalY(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame,
		glm::radians(degrees),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void GraphicsObject::RotateLocalZ(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame, 
		glm::radians(degrees), 
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
}

void GraphicsObject::Update(double elapsedSeconds)
{
	if (animation) { animation->Update(elapsedSeconds); }	
}
