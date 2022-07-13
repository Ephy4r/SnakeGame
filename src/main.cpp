#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader/Shader.hpp"

const char* fragmentSource = "#version 460 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0);\n"
"}\0";

const char* vertexSource = "#version 460 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"ourColor = aColor;\n"
"}\0";


float vertices[] = {
	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

int indices[] =
{
	0, 1, 3,
	1, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int args, char argv[])
{
	// инициализируем glfw
	glfwInit();	
	// указываем версию OpenGL и core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// создаем окно
	GLFWwindow* window = glfwCreateWindow(800, 600, "pesbarbos", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window wasn't initialised" << std::endl;
		glfwTerminate();
		return -1;
	}
	// делаем это окно активным(или основным, я не помню)
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// инициализруем glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("C:/Users/Ksovox/OpenGl/SnakeGame/res/shaders/shader.vs"
				, "C:/Users/Ksovox/OpenGl/SnakeGame/res/shaders/shader.fs");

	shader.use();

	unsigned int VBO, VAO;												
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// привязываю VAO
	glBindVertexArray(VAO);
	// делаю все операции, которые потом будет производить VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);									
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// цикл рендеринга
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// меняем буферы цвета
		glfwSwapBuffers(window);
		// проверка событий(и вызов соответствующих функций)
		glfwPollEvents();
	}
	// закрытие окна
	glfwTerminate();
	return 0;
}