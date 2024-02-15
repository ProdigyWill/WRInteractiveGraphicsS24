#pragma once
#include <string>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>
#include "BaseObject.h"
#include <glad/glad.h>
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
class Renderer {
private:
    std::shared_ptr<Shader> shader;
    GLuint vaoId;

public:
    Renderer(std::shared_ptr<Shader>& shader);

    inline const std::shared_ptr<Shader>& getShader() const {
        return shader;
    }
    Renderer(const std::shared_ptr<Shader>& shader) : shader(shader) {
        // Generate VAO
        glGenVertexArrays(1, &vaoId);
    }
    ~Renderer();
    void RenderObject(const GraphicsObject& object);
    void allocateVertexBuffers(const std::vector<std::shared_ptr<GraphicsObject>>& objects);
    void RenderScene(const std::shared_ptr<Scene> scene, const glm::mat4& view);
};

