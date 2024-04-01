#pragma once
#include <memory>
#include "VertexBuffer.h"
#include <glm.hpp>
#include "IndexBuffer.h"
class Generate
{
public:
	static std::shared_ptr<VertexBuffer> Cuboid(
		float width, float height, float depth,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0 });
	static std::shared_ptr<VertexBuffer> CuboidNorm(
		float width, float height, float depth,
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0 });
	static std::shared_ptr<VertexBuffer> XZPlane(
		float width, float depth,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0 });
	static std::shared_ptr<VertexBuffer> XZPlaneNorm(
		float width, float depth,
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0 });
	static std::shared_ptr<VertexBuffer> XYPlane(
		float width, float height,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f },
		glm::vec2 tex = { 1.0f, 1.0 });
	static void GenerateXZCircle(
		float radius,
		int steps,
		std::shared_ptr<VertexBuffer> buffer,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f });
	static void LineCircleIndexes(
		std::shared_ptr<IndexBuffer>& bufferToFill,
		int numberOfLineSegments, bool isClosed = true);
	static void GenerateCylinder(
		float radius,
		int steps,
		float height,
		std::shared_ptr<VertexBuffer> buffer,
		glm::vec3 color = { 1.0f, 1.0f, 1.0f });
	static void LineCylinderIndexes(
		std::shared_ptr<IndexBuffer>& bufferToFill,
		int numberOfLineSegments, bool isClosed = true);
};

