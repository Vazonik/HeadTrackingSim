#include "App.h"

App* App::instance = nullptr;

App::App() : running(true), width(800), height(600)
{
	if (!glfwInit())
	{
		terminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, "Perspective Simulator", nullptr, nullptr);

	input = new Input();

	if (!window)
	{
		terminate();
		return;
	}

	glfwSetKeyCallback(window, invokeInput);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		terminate();
		return;
	}
}

void App::loop()
{
	while (running)
	{
		update();
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
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}
	else
	{
		glClearColor(0.1f, 1.0f, 1.0f, 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
}

App::~App()
{
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
	std::cout << window << " " << key << " " << scancode << " " << action << " " << mods << std::endl;
}