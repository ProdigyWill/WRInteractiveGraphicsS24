#include "Renderer.h"
#include "glm/glm.hpp"

Renderer::Renderer(std::shared_ptr<Shader>& shader)
{
	this->shader = shader;
	glGenVertexArrays(1, &this->vaoID);
}

void Renderer::AllocateVertexBuffers(const std::vector<std::shared_ptr<GraphicsObject>>& objects)
{
	glBindVertexArray(this->vaoID);
	for (auto& object : objects)
	{
		object->StaticAllocateVertexBuffer();
	}
	glBindVertexArray(0);
}

void Renderer::RenderScene(const Camera& camera)
{
    if (this->shader->IsCreated()) {
        glUseProgram(this->shader->GetShaderProgram());
        glBindVertexArray(this->vaoID);

        // Send view and projection matrices to the GPU
        shader->SendMat4Uniform("view", view);
        shader->SendMat4Uniform("projection", projection);

        // Get global and local light data from the scene
        Light& globalLight = scene->GetGlobalLight();
        Light& localLight = scene->GetLocalLight();

        // Send global light data to the GPU
        shader->SendVec3Uniform("globalLightPosition", globalLight.position);
        shader->SendVec3Uniform("globalLightColor", globalLight.color);
        shader->SendFloatUniform("globalLightIntensity", globalLight.intensity);

        // Send local light data to the GPU
        shader->SendVec3Uniform("localLightPosition", localLight.position);
        shader->SendVec3Uniform("localLightColor", localLight.color);
        shader->SendFloatUniform("localLightIntensity", localLight.intensity);

        // Send camera position to the GPU
        shader->SendVec3Uniform("viewPosition", camera.GetPosition());

        // Render the objects in the scene
        for (auto& object : scene->GetObjects()) {
            RenderObject(*object);
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glUseProgram(0);
        glBindVertexArray(0);
    }
}

void Renderer::SetScene(std::shared_ptr<Scene> scene)
{
	this->scene = scene;
}

void Renderer::SetView(glm::mat4 view)
{
	this->view = view;
}

void Renderer::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

void Renderer::RenderObject(GraphicsObject& object)
{
	shader->SendMat4Uniform("world", object.GetReferenceFrame());
	auto& buffer = object.GetVertexBuffer();
	buffer->Select();

    Material& material = object.GetMaterial();
    shader->SendFloatUniform("materialAmbientIntensity", material.ambientIntensity);
    shader->SendFloatUniform("materialSpecularIntensity", material.specularIntensity);
    shader->SendFloatUniform("materialShininess", material.shininess);

    if (buffer->HasTexture())
    {
        shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
        buffer->GetTexture()->SelectToRender(buffer->GetTextureUnit());
    }

    buffer->SetUpAttributeInterpretration();

    if (object.IsIndexed()) {
        auto& indexBuffer = object.GetIndexBuffer();
        glDrawElements(buffer->GetPrimitiveType(), indexBuffer->GetNumberOfVertices(),
            GL_UNSIGNED_SHORT, (void*)0);
    }
    else {
        glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());
    }

    // Recursively render the children
    auto& children = object.GetChildren();
    for (auto& child : children) {
        RenderObject(*child);
    }
}