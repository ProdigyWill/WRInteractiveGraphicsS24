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

void Renderer::RenderScene()
{
	if (this->shader->IsCreated()) {
		glUseProgram(this->shader->GetShaderProgram());
		glBindVertexArray(this->vaoID);
		shader->SendMat4Uniform("view", view);
		shader->SendMat4Uniform("projection", projection);
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

void Renderer::RenderObject(const GraphicsObject& object)
{
	shader->SendMat4Uniform("world", object.GetReferenceFrame());
	auto& buffer = object.GetVertexBuffer();
	buffer->Select();

	if (buffer->HasTexture())
	{
		shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
		buffer->GetTexture()->SelectToRender(buffer->GetTextureUnit());
	}

	buffer->SetUpAttributeInterpretration();
	glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());

	// Recursively render the children
	auto& children = object.GetChildren();
	for (auto& child : children) {
		RenderObject(*child);
	}
}