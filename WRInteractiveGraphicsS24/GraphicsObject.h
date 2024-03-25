#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "VertexBuffer.h"
#include "GraphicsStructures.h"
#include "IndexBuffer.h"

class IAnimation;

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

public:
	GraphicsObject();
	virtual ~GraphicsObject();

	inline bool IsIndexed() const { return indexBuffer != nullptr; }
	const glm::mat4 GetReferenceFrame() const;
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; }
	Material& GetMaterial() { return material; };
	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void CreateIndexBuffer();
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetReferenceFrame(glm::mat4 referenceFrame);
	void SetAnimation(std::shared_ptr<IAnimation> animation);
	void PointAt(glm::vec3 point);
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

