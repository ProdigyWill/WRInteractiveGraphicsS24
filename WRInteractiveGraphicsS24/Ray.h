#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GeometricLine.h"
#include "GeometricPlane.h"


class BoundingBox;
class GraphicsObject;

class Ray
{
protected:
	glm::vec3 rayStart{};
	glm::vec3 rayDir{};

public:
	Ray() = default;
	~Ray() = default;
	void Create(
		float screenX, float screenY,
		const glm::mat4& proj, const glm::mat4& view);

	void SetStart(glm::vec3 start) { rayStart = start; }
	void SetDirection(glm::vec3 dir) { rayDir = glm::normalize(dir); }

	const glm::vec3& GetStart() const { return rayStart; }
	const glm::vec3& GetDirection() const { return rayDir; }

	Intersection GetIntersectionWithPlane(const GeometricPlane& plane) const;
	Intersection GetIntersectionWithBoundingBox(
		const BoundingBox& boundingBox) const;
	glm::vec3 GetIntersectionPoint(float offset) const;
	bool IsIntersectingObject(const GraphicsObject& object) const;

};

