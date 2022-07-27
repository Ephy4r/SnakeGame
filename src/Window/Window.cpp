#include "Window.hpp"

Window::Window(int width, int height, std::string title)
	: m_width(width), m_height(height), m_title(title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(m_width, m_height, "pes" , nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Window wasn't initialised" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	// инициализруем glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

GLFWwindow* Window::getWindow()
{
	return window;
}