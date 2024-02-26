#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TextFile.h"
#include "GraphicsEnvironment.h"

struct VertexData {
	glm::vec3 position, color;
	glm::vec2 tex;
};

static void SetUpScene(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	const std::string vertexFilePath = "basic.vert.glsl";
	const std::string fragmentFilePath = "basic.frag.glsl";

	TextFile vertexFile(vertexFilePath);
	TextFile fragmentFile(fragmentFilePath);

	shader = std::make_shared<Shader>(vertexFile.getData(), fragmentFile.getData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");

	scene = std::make_shared<Scene>();

	std::shared_ptr<GraphicsObject> square = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexAttribute("position", 0, 3);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	square->SetVertexBuffer(buffer);
	scene->AddObject(square);

	std::shared_ptr<GraphicsObject> triangle = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(6);
	buffer2->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexAttribute("position", 0, 3);
	buffer2->AddVertexAttribute("color", 1, 3, 3);
	triangle->SetVertexBuffer(buffer2);
	triangle->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));
	scene->AddObject(triangle);

	std::shared_ptr<GraphicsObject> line = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer3 = std::make_shared<VertexBuffer>(6);
	buffer3->SetPrimitiveType(GL_LINES);
	buffer3->AddVertexData(6, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexData(6, 0.0f, -2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexAttribute("position", 0, 3);
	buffer3->AddVertexAttribute("color", 1, 3, 3);
	line->SetVertexBuffer(buffer3);
	line->SetPosition(glm::vec3(5.0f, -10.0f, 0.0f));
	triangle->AddChild(line);
}

static void SetUpTexturedScene(std::shared_ptr<Shader>& textureShader, std::shared_ptr<Scene>& textureScene) {
	TextFile textureVertexFile("texture.vert.glsl");
	TextFile textureFragmentFile("texture.frag.glsl");

	textureShader = std::make_shared<Shader>(textureVertexFile.getData(), textureFragmentFile.getData());
	textureShader->AddUniform("projection");
	textureShader->AddUniform("world");
	textureShader->AddUniform("view");
	textureShader->AddUniform("texUnit");

	std::shared_ptr<Texture> sharedTexture = std::make_shared<Texture>();
	sharedTexture->SetWidth(4);
	sharedTexture->SetHeight(4);
	sharedTexture->SetWrapS(GL_CLAMP_TO_EDGE);
	sharedTexture->SetWrapT(GL_CLAMP_TO_EDGE);
	sharedTexture->SetMagFilter(GL_LINEAR);

	unsigned char textureData[] = {
		255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
		255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255
	};

	sharedTexture->SetTextureData(64, textureData);
	textureScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> texturedObject = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> texturedBuffer = std::make_shared<VertexBuffer>(8);

	texturedBuffer->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	texturedBuffer->AddVertexData(8, -50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	texturedBuffer->AddVertexData(8, 50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f);

	texturedBuffer->AddVertexAttribute("position", 0, 3, 0);
	texturedBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	texturedBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	texturedBuffer->SetTexture(sharedTexture);
	texturedObject->SetVertexBuffer(texturedBuffer);
	texturedObject->SetPosition(glm::vec3(-75.0f, -25.0f, 0.0f)); 
	textureScene->AddObject(texturedObject);


	//Second Object
	std::shared_ptr<GraphicsObject> texturedObject2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> texturedBuffer2 = std::make_shared<VertexBuffer>(8);
	std::shared_ptr<Texture> sharedTexture2 = std::make_shared<Texture>();

	texturedBuffer2->AddVertexData(8, -25.0f, 25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer2->AddVertexData(8, -25.0f, -25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer2->AddVertexData(8, 25.0f, -25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer2->AddVertexData(8, -25.0f, 25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer2->AddVertexData(8, 25.0f, -25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer2->AddVertexData(8, 25.0f, 25.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	texturedBuffer2->AddVertexAttribute("position", 0, 3, 0);
	texturedBuffer2->AddVertexAttribute("vertexColor", 1, 3, 3);
	texturedBuffer2->AddVertexAttribute("texCoord", 2, 2, 6);

	sharedTexture2->LoadTextureDataFromFile("planet05.png"); 
	texturedBuffer2->SetTexture(sharedTexture2);
	texturedObject2->SetVertexBuffer(texturedBuffer2);
	texturedObject2->SetPosition(glm::vec3(75.0f, 25.0f, 0.0f));
	textureScene->AddObject(texturedObject2);
}

static void SetUp3DScene1(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene) {
	TextFile textureVertexFile("texture.vert.glsl");
	TextFile textureFragmentFile("texture.frag.glsl");

	shader = std::make_shared<Shader>(textureVertexFile.getData(), textureFragmentFile.getData());
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("texUnit");

	std::shared_ptr<Texture> sharedTexture = std::make_shared<Texture>();
	sharedTexture->SetWidth(4);
	sharedTexture->SetHeight(4);

	// Create the texture data
	unsigned char* textureData = new unsigned char[] {
			0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255
	};

	sharedTexture->SetTextureData(sizeof(textureData), textureData);
	scene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> texturedObject = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> texturedBuffer = std::make_shared<VertexBuffer>(8);

	// Front face
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	// Right face
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	// Back face  
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	// Left face 
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	// Top face	
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, 5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	// Bottom face 
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, 5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	texturedBuffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	texturedBuffer->AddVertexData(8, -5.0f,-5.0f,-5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	texturedBuffer->AddVertexAttribute("position", 0, 3, 0);
	texturedBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	texturedBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	texturedBuffer->SetTexture(sharedTexture);
	texturedObject->SetVertexBuffer(texturedBuffer);
	texturedObject->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	scene->AddObject(texturedObject);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GraphicsEnvironment glfw;
	glfw.Init(4, 3);

	bool created = glfw.SetWindow(
		1200, 800, "ETSU Computing Interactive Graphics");
	if (created == false) return -1;

	bool loaded = glfw.InitGlad();
	if (loaded == false) return -1;

	glfw.SetupGraphics();

	//std::shared_ptr<Shader> shader;
	//std::shared_ptr<Scene> scene;
	//SetUpScene(shader, scene);

	//std::shared_ptr<Shader> textureShader;
	//std::shared_ptr<Scene> textureScene;
	//SetUpTexturedScene(textureShader, textureScene);
	
	//glfw.CreateRenderer("basic", shader);
	//glfw.GetRenderer("basic")->SetScene(scene);
	//glfw.CreateRenderer("texture", textureShader);
	//glfw.GetRenderer("texture")->SetScene(textureScene);
	//glfw.StaticAllocate();

	//glfw.Run2D();

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
	SetUp3DScene1(shader, scene);

	glfw.CreateRenderer("basic", shader);
	glfw.GetRenderer("basic")->SetScene(scene);
	glfw.StaticAllocate();

	glfw.Run3D();


	return 0;
}

