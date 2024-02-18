#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include <glm/glm.hpp>

class Renderer : public BaseObject
{
private:
	unsigned int vaoID;
	std::shared_ptr<Shader> shader;

public:
	Renderer(std::shared_ptr<Shader>& shader);
	~Renderer() = default;

	inline std::shared_ptr<Shader> GetShader() const { return shader; }

	void AllocateVertexBuffers(const std::vector<std::shared_ptr<GraphicsObject>>& objects);
	void RenderScene(std::shared_ptr<Scene>& scene, glm::mat4& view);

private:
	void RenderObject(const GraphicsObject& object);
};