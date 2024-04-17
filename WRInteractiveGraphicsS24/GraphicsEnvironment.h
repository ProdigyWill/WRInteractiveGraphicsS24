#pragma once
#include "BaseObject.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <iostream>
#include "Renderer.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "GraphicsStructures.h"
#include "Ray.h"
class GraphicsEnvironment : public BaseObject
{
private:
	GLFWwindow* window;
	std::unordered_map<std::string, std::shared_ptr<Renderer>> rendererMap;
	std::shared_ptr<ObjectManager> objectManager = std::make_shared<ObjectManager>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	static GraphicsEnvironment* self;
	MouseParams mouse;
	Ray mouseRay;
	bool lookWithMouse = false;
public:
	GraphicsEnvironment();
	~GraphicsEnvironment();
	inline GLFWwindow* GetWindow() const { return window; }
	inline std::shared_ptr<ObjectManager> GetManager() const { return objectManager; }
	static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);
	bool SetWindow(unsigned int width, unsigned int height, const std::string& title);
	bool InitGlad();
	void Init(unsigned int majorVersion, unsigned int minorVersion);
	void SetupGraphics();
	void CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader);
	void StaticAllocate();
	void Render();
	void ProcessInput(GLFWwindow* window, double elapsedSeconds);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void OnMouseMove(GLFWwindow* window, double mouseX, double mouseY);
	static glm::mat4 CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
	Ray GetMouseRay(const glm::mat4& projection, const glm::mat4& view);
	void Run2D();
	void Run3D();
	void AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object);
	std::shared_ptr<Renderer> GetRenderer(const std::string& name);
	std::shared_ptr<GraphicsObject> GetObject(const std::string& name) {
		return objectManager->GetObject(name);
	};
};

