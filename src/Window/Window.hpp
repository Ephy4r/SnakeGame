#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
	GLFWwindow* window;
	int m_width;
	int m_height;
	std::string m_title;
public:
	Window(int width, int height, std::string title);

	int getWidth();
	int getHeight();
	GLFWwindow* getWindow();
	bool shouldClose();
}; 