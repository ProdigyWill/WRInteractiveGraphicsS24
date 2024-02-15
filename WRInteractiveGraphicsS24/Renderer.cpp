#include "Renderer.h"
#include "glm/glm.hpp";

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

void Renderer::RenderScene(std::shared_ptr<Scene>& scene, glm::mat4& view)
{
	if (this->shader->IsCreated()) {
		glUseProgram(this->shader->GetShaderProgram());
		glBindVertexArray(this->vaoID);
		shader->SendMat4Uniform("view", view);
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