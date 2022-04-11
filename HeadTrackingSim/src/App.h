#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Input.h"


class App
{
private:
	App();
	~App();
	static App* instance;
public:
	static App* create();
	static App* getInstance();
	static void terminate();
	static void frameBufferResize(GLFWwindow* window, int width, int height);
	static void invokeInput(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	GLFWwindow* window;
	void update();
	void render();
	bool running;
	int width;
	int height;
	Input *input;
public:
	void loop();
	int getWidth() const;
	int getHeight() const;
};