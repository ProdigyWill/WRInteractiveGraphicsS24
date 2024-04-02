#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float halfDepth = depth / 2;
	// Front face
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t);
	// Right face
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);
	// Back face  
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);
	// Left face 
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t);
	// Top face	
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);
	// Bottom face 
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);
	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::CuboidNorm(float width, float height, float depth, glm::vec4 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float halfDepth = depth / 2;
	// Front face
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 1.0f, tex.s, tex.t);
	// Right face		  
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 1.0f, 0.0f, 0.0f, tex.s, tex.t);
	// Back face  		 
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 0.0f, -1.0f, tex.s, tex.t);
	// Left face 		  
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, -1.0f, 0.0f, 0.0f, tex.s, tex.t);
	// Top face			  
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, tex.t);
	// Bottom face 		  
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, -1.0f, 0.0f, tex.s, tex.t);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("vertexNormal", 2, 3, 7); 
	buffer->AddVertexAttribute("texCoord", 3, 2, 10);
	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);
	float halfWidth = width / 2;
	float halfDepth = depth / 2;
	buffer->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);
	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZPlaneNorm(float width, float depth, glm::vec4 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);
	float halfWidth = width / 2;
	float halfDepth = depth / 2;
	buffer->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	buffer->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, 0.0f, tex.t);
	buffer->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, 0.0f);
	buffer->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f, tex.s, tex.t);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	buffer->AddVertexAttribute("texCoord", 3, 2, 10);
	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XYPlane(float width, float height, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	buffer->AddVertexData(8, -halfWidth, halfHeight, 0, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, 0.0f, 0.0f);
	buffer->AddVertexData(8, halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, -halfWidth, halfHeight, 0, color.r, color.g, color.b, 0.0f, tex.t);
	buffer->AddVertexData(8, halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0.0f);
	buffer->AddVertexData(8, halfWidth, halfHeight, 0, color.r, color.g, color.b, tex.s, tex.t);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);
	return buffer;
}

void Generate::GenerateXZCircle(float radius, int steps, std::shared_ptr<VertexBuffer> buffer, glm::vec3 color)
{
	float x, z, thetaRadians;
	for (float theta = 0.0f; theta < 360; theta += steps) {
		thetaRadians = glm::radians(theta);
		x = radius * cosf(thetaRadians);
		z = radius * sinf(thetaRadians);
		buffer->AddVertexData(6, x, 0.0f, z, color.r, color.g, color.b);
	}
	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
}

void Generate::LineCircleIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments, bool isClosed)
{
	unsigned short nextIndex;
	if (isClosed)
	{
		for (unsigned short index = 0; index < numberOfLineSegments; index++) {
			bufferToFill->AddIndexData(index);
			nextIndex = (index + 1) % static_cast<unsigned short>(numberOfLineSegments);
			bufferToFill->AddIndexData(nextIndex);
		}
	}
	else {
		for (unsigned short index = 0; index < numberOfLineSegments - 1; index++) {
			bufferToFill->AddIndexData(index);
			nextIndex = index + 1;
			bufferToFill->AddIndexData(nextIndex);
		}
	}
}

void Generate::GenerateCylinder(float radius, int steps, float height, std::shared_ptr<VertexBuffer> buffer, glm::vec3 color)
{
	float x, z, thetaRadians, halfHeight=height/2;
	//Top Circle
	for (float theta = 0.0f; theta < 360; theta += steps) {
		thetaRadians = glm::radians(theta);
		x = radius * cosf(thetaRadians);
		z = radius * sinf(thetaRadians);
		buffer->AddVertexData(6, x, halfHeight, z, color.r, color.g, color.b);
	}
	//Bottom Circle
	for (float theta = 0.0f; theta < 360; theta += steps) {
		thetaRadians = glm::radians(theta);
		x = radius * cosf(thetaRadians);
		z = radius * sinf(thetaRadians);
		buffer->AddVertexData(6, x, -halfHeight, z, color.r, color.g, color.b);
	}
	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
}

void Generate::LineCylinderIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments, bool isClosed)
{
	unsigned short nextIndex;
	int halfNumberOfLineSegments = numberOfLineSegments / 2;
	for (unsigned short index = 0; index < halfNumberOfLineSegments; index++) {
		bufferToFill->AddIndexData(index);
		nextIndex = (index + 1) % static_cast<unsigned short>(halfNumberOfLineSegments);
		bufferToFill->AddIndexData(nextIndex);
	}

	for (unsigned short index = halfNumberOfLineSegments; index < numberOfLineSegments; index++) {
		bufferToFill->AddIndexData(index);
		nextIndex = (index + 1) % static_cast<unsigned short>(numberOfLineSegments);
		if (nextIndex == 0) { nextIndex = halfNumberOfLineSegments; }
		bufferToFill->AddIndexData(nextIndex);
	}

	for (unsigned short index = 0; index < halfNumberOfLineSegments; index++) {
		bufferToFill->AddIndexData(index);
		nextIndex = index + halfNumberOfLineSegments;
		bufferToFill->AddIndexData(nextIndex);
	}
}

