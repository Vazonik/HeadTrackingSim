#include <glad/glad.h>
#include "App.h"

#include "utils/Debug.h"

App* App::instance = nullptr;

App::App() : running(true), width(800), height(600)
{
	Debug::log("GLFW initialization has started");
	if (!glfwInit())
	{
		Debug::error("GLFW initialization has failed");
		terminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	Debug::log("Creating the window...");
	window = glfwCreateWindow(width, height, "Perspective Simulator", nullptr, nullptr);

	input = new Input();

	if (!window)
	{
		Debug::error("Window creation failed");
		terminate();
		return;
	}

	glfwSetKeyCallback(window, invokeInput);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::error("GLAD initialization failed");
		terminate();
		return;
	}

	shaders.loadAll();
	gui.initialize(window);
}

void App::loop()
{
	while (running)
	{
		update();
		gui.newFrame();
		render();

		if (glfwWindowShouldClose(window))
		{
			running = false;
			break;
		}
	}
}

void App::update()
{
	glfwPollEvents();
}

void App::render()
{
	if (input->isKeyDown(GLFW_KEY_A))
	{
		glClearColor(0.1f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	gui.render();

	glfwSwapBuffers(window);
}

App::~App()
{
	gui.terminate();
	shaders.unloadAll();

	delete input;
	input = nullptr;

	glfwDestroyWindow(window);
	glfwTerminate();
}

App* App::create()
{
	if (!instance)
	{
		instance = new App();
		return instance;
	}
	
	throw std::exception("The application instance has already been created");
}

App* App::getInstance()
{
	return instance;
}

void App::terminate()
{
	delete instance;
	instance = nullptr;
}

int App::getWidth() const
{
	return width;
}

int App::getHeight() const
{
	return height;
}

void App::frameBufferResize(GLFWwindow* window, const int width, const int height)
{
	const auto appInstance = getInstance();
	appInstance->width = width;
	appInstance->height = height;
}

void App::invokeInput(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
{
	getInstance()->input->setKeyState(key, action != GLFW_RELEASE);
	Debug::log(std::to_string((int)window) + " " + std::to_string(key) + " " + std::to_string(scancode) + " " + std::to_string(action) + " " + std::to_string(mods));
}