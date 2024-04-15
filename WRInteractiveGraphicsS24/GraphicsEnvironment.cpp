#include "GraphicsEnvironment.h"
#include <iostream>
#include "Timer.h"
#include "RotateAnimation.h"
#include "MoveAnimation.h"
GraphicsEnvironment* GraphicsEnvironment::self;

GraphicsEnvironment::GraphicsEnvironment()
{
	self = this;
}

GraphicsEnvironment::~GraphicsEnvironment()
{
	glfwTerminate();
}

void GraphicsEnvironment::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool GraphicsEnvironment::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL) {
		Log("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool GraphicsEnvironment::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log("Failed to initialize GLAD");
		return false;
	}
	return true;
}

void GraphicsEnvironment::Init(unsigned int majorVersion, unsigned int minorVersion)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void GraphicsEnvironment::SetupGraphics()
{
	//Antialiasing
	glEnable(GL_MULTISAMPLE);

	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	//Alpha Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetFramebufferSizeCallback(window, OnWindowSizeChanged);

	//Mouse
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}

void GraphicsEnvironment::CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(shader);
	rendererMap[name] = renderer;
}

void GraphicsEnvironment::StaticAllocate()
{
	for (auto& pair : rendererMap) {
		pair.second->AllocateVertexBuffers(pair.second->GetScene()->GetObjects());
	}
}

void GraphicsEnvironment::Render()
{
	for (const auto& pair : rendererMap) {
		pair.second->RenderScene(*camera);
	}
}

void GraphicsEnvironment::ProcessInput(GLFWwindow* window, double elapsedSeconds)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->MoveForward(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->MoveBackward(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->MoveLeft(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->MoveRight(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera->MoveUp(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera->MoveDown(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera->LookRight(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera->LookLeft(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->LookUp(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->LookDown(elapsedSeconds);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
		lookWithMouse = !lookWithMouse;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		lookWithMouse = false;
		camera->SetPosition({ 0, 5, 30 });
		camera->SetLookFrame(glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 1, 0)));
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		lookWithMouse = false;
		camera->SetPosition({ 30, 5, 0 });
		camera->SetLookFrame(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0)));
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		lookWithMouse = false;
		camera->SetPosition({ 0, 5, -30 });
		camera->SetLookFrame(glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 1, 0)));
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		lookWithMouse = false;
		camera->SetPosition({ -30, 5, 0 });
		camera->SetLookFrame(glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0, 1, 0)));
		return;
	}
}

void GraphicsEnvironment::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::static_pointer_cast<MoveAnimation>(self->objectManager->GetObject("apple")->GetAnimation())->ChangeState();
	}
}

void GraphicsEnvironment::OnMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
	self->mouse.x = mouseX;
	self->mouse.y = mouseY;

	self->mouse.normalizedX = (2.0 * self->mouse.x) / self->mouse.windowWidth - 1.0;
	self->mouse.normalizedY = 1.0 - (2.0 * self->mouse.y) / self->mouse.windowHeight;

	float xPercent = static_cast<float>(self->mouse.x / self->mouse.windowWidth);
	float yPercent = static_cast<float>(self->mouse.y / self->mouse.windowHeight);

	self->mouse.spherical.theta = 90.0f - (xPercent * 180); // left/right
	self->mouse.spherical.phi = 180.0f - (yPercent * 180); // up/down
}

glm::mat4 GraphicsEnvironment::CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up)
{
	glm::vec3 right = glm::cross(direction, up);
	right = glm::normalize(right);

	glm::vec3 vUp = glm::cross(right, direction);
	vUp = glm::normalize(vUp);

	glm::mat4 view(1.0f);
	view[0] = glm::vec4(right, 0.0f);
	view[1] = glm::vec4(up, 0.0f);
	view[2] = glm::vec4(direction, 0.0f);
	view[3] = glm::vec4(position, 1.0f);
	return glm::inverse(view);
}

Ray GraphicsEnvironment::GetMouseRay(const glm::mat4& projection, const glm::mat4& view)
{
	Ray ray;

	// Convert mouse screen coordinates to clip space
	float rayX = (float)(2.0f * mouse.normalizedX) - 1.0f;
	float rayY = 1.0f - (float)(2.0f * mouse.normalizedY);

	// Create ray
	ray.Create(rayX, rayY, projection, view);

	return ray;
}

void GraphicsEnvironment::Run2D()
{
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };
	float angle = 0, childAngle = 0;
	float cameraX = -10, cameraY = 0;
	glm::mat4 view;

	ImGuiIO& io = ImGui::GetIO();
	while (!glfwWindowShouldClose(window)) {
		//ProcessInput(window);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float aspectRatio = width / (height * 1.0f);

		float left = -100.0f;
		float right = 100.0f;
		float bottom = -100.0f;
		float top = 100.0f;
		left *= aspectRatio;
		right *= aspectRatio;
		glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		view = CreateViewMatrix(
			glm::vec3(cameraX, cameraY, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		// Update the objects in the scene
		for (auto& object : GetRenderer("basic")->GetScene()->GetObjects()) {
			object->ResetOrientation();
			object->RotateLocalZ(angle);
			for (auto& child : object->GetChildren()) {
				child->ResetOrientation();
				child->RotateLocalZ(childAngle);
			}
		}

		GetRenderer("basic")->SetProjection(projection);
		GetRenderer("basic")->SetView(view);
		GetRenderer("basic")->RenderScene(*camera);

		GetRenderer("texture")->SetProjection(projection);
		GetRenderer("texture")->SetView(view);
		GetRenderer("texture")->RenderScene(*camera);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetRenderer("basic")->GetShader()->GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("Angle", &angle, 0, 360);
		ImGui::SliderFloat("Child Angle", &childAngle, 0, 360);
		ImGui::SliderFloat("Camera X", &cameraX, left, right);
		ImGui::SliderFloat("Camera Y", &cameraY, bottom, top);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void GraphicsEnvironment::Run3D()
{
	int width, height;
	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 100.0f;
	float fieldOfView = 60;


	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	ImGuiIO& io = ImGui::GetIO();
	double elapsedSeconds;
	bool correctGamma = false;
	Timer timer;
	Light& localLight = GetRenderer("basic")->GetScene()->GetLocalLight();
	Light& globalLight = GetRenderer("basic")->GetScene()->GetGlobalLight();

	//Rotation
	std::shared_ptr<RotateAnimation> rotateAnimation =
		std::make_shared<RotateAnimation>();
	rotateAnimation->SetObject(objectManager->GetObject("crate"));
	objectManager->GetObject("crate")->SetAnimation(rotateAnimation);

	//Movement
	std::shared_ptr<MoveAnimation> moveAnimation =
		std::make_shared<MoveAnimation>();
	moveAnimation->SetObject(objectManager->GetObject("apple"));
	objectManager->GetObject("apple")->SetAnimation(moveAnimation);

	camera->SetPosition({ 0.0f, 0.0f, 20.0f });
	camera->SetLookFrame(glm::mat4(1.0f));

	Ray ray;
	glm::vec3 rayStart{};
	glm::vec3 rayDir{};
	GeometricPlane plane;
	plane.SetDistanceFromOrigin(objectManager->GetObject("floor")->GetReferenceFrame()[3].y);
	Intersection planeIntersection;

	objectManager->SetBehaviorDefaults();

	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();
		ProcessInput(window, elapsedSeconds);
		glfwGetWindowSize(window, &width, &height);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if (correctGamma) {
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else {
			glDisable(GL_FRAMEBUFFER_SRGB);
		}

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}

		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		// Set up the ray
		ray.Create((float)mouse.normalizedX, (float)mouse.normalizedY, projection, view);
		rayStart = ray.GetStart();
		rayDir = ray.GetDirection();
		planeIntersection = ray.GetIntersectionWithPlane(plane);

		if (planeIntersection.isIntersecting) {
			objectManager->GetObject("cylinder")->SetPosition({ planeIntersection.point.x, 0.0f, planeIntersection.point.z });

		}
		else {
			objectManager->GetObject("cylinder")->SetPosition({ 10.0f, 0.0f, 7.0f });
		}

		if (lookWithMouse) {
			camera->SetLookFrame(mouse.spherical.ToMat4());
		}

		self->mouse.windowHeight = height;
		self->mouse.windowWidth = width;	
		view = camera->LookForward();

		HighlightParams hp = { {}, &ray };
		objectManager->GetObject("TextureObject1")->
			SetBehaviorParameters("highlight", hp);
		objectManager->GetObject("crate")->
			SetBehaviorParameters("highlight", hp);
		objectManager->GetObject("apple")->
			SetBehaviorParameters("highlight", hp);

		objectManager->Update(elapsedSeconds);

		objectManager->GetObject("light")->SetPosition(GetRenderer("basic")->GetScene()->GetLocalLight().position);
		objectManager->GetObject("light")->PointAt(camera->GetPosition());

		// Render the object
		GetRenderer("basic")->SetProjection(projection);
		GetRenderer("basic")->SetView(view);
		GetRenderer("basic")->RenderScene(*camera);
		GetRenderer("light")->SetProjection(projection);
		GetRenderer("light")->SetView(view);
		GetRenderer("light")->RenderScene(*camera);
		GetRenderer("circle")->SetProjection(projection);
		GetRenderer("circle")->SetView(view);
		GetRenderer("circle")->RenderScene(*camera);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetRenderer("basic")->GetShader()->GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::Text("Mouse: (%.0f, %.0f)", mouse.x, mouse.y);
		ImGui::SliderFloat("Global Intensity", &globalLight.intensity, 0, 1);
		ImGui::SliderFloat("Local Intensity", &localLight.intensity, 0, 1);
		ImGui::DragFloat3("Local Light Position", &localLight.position.x);
		ImGui::Checkbox("Correct gamma", &correctGamma);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void GraphicsEnvironment::AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	objectManager->SetObject(name, object);
}

std::shared_ptr<Renderer> GraphicsEnvironment::GetRenderer(const std::string& name)
{
	return rendererMap[name];
}
