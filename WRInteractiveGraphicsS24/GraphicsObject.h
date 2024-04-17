#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "VertexBuffer.h"
#include "GraphicsStructures.h"
#include "IndexBuffer.h"


class IAnimation;
class BoundingBox;
class Ray;

class GraphicsObject
{
protected:
	glm::mat4 referenceFrame;
	std::shared_ptr<VertexBuffer> buffer;
	std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
	GraphicsObject* parent;
	std::vector<std::shared_ptr<GraphicsObject>> children;
	std::shared_ptr<IAnimation> animation = nullptr;
	Material material;
	std::shared_ptr<BoundingBox> boundingBox = nullptr;
	std::unordered_map<std::string, std::shared_ptr<IBehavior>> behaviorMap;

public:
	GraphicsObject();
	virtual ~GraphicsObject();

	inline bool IsIndexed() const { return indexBuffer != nullptr; }
	BoundingBox& GetBoundingBox() const { return *boundingBox; }
	inline bool HasBoundingBox() const { return boundingBox != nullptr; }
	bool IsIntersectingWithRay(const Ray& ray) const;
	const glm::mat4 GetReferenceFrame() const;
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; }
	std::shared_ptr<IAnimation> GetAnimation() { return animation; }
	Material& GetMaterial() { return material; }
	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void CreateIndexBuffer();
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetReferenceFrame(glm::mat4 referenceFrame);
	void SetAnimation(std::shared_ptr<IAnimation> animation);
	void SetBehaviorDefaults();
	void SetBehaviorParameters(std::string name, IParams& params);
	void PointAt(glm::vec3 point);
	void CreateBoundingBox(float width, float height, float depth);
	void AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior);
	inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const {
		return buffer;
	}
	inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const {
		return indexBuffer;
	}
	void StaticAllocateVertexBuffer();

	void AddChild(std::shared_ptr<GraphicsObject> child);
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetChildren() const {
		return children;
	}

	void SetPosition(const glm::vec3& position);
	void ResetOrientation();
	void RotateLocalX(float degrees);
	void RotateLocalY(float degrees);
	void RotateLocalZ(float degrees);
	void Update(double elapsedSeconds);
};