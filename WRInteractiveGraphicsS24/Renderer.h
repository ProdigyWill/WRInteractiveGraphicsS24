#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include "Camera.h"

class Renderer : public BaseObject
{
private:
	unsigned int vaoID;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
	glm::mat4 view;
	glm::mat4 projection;

public:
	Renderer(std::shared_ptr<Shader>& shader);
	~Renderer() = default;

	inline std::shared_ptr<Shader> GetShader() const { return shader; }
	inline std::shared_ptr<Scene> GetScene() const { return scene; }

	void AllocateVertexBuffers(const std::vector<std::shared_ptr<GraphicsObject>>& objects);
	void RenderScene(const Camera& camera);
	void SetScene(std::shared_ptr<Scene> scene);
	void SetView(glm::mat4 view);
	void SetProjection(glm::mat4 projection);
private:
	void RenderObject(GraphicsObject& object);
};