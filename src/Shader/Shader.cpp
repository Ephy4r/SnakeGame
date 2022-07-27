#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::stringstream vertexStream;
	std::stringstream fragmentStream;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.open(vertexPath);
	vertexStream << vertexFile.rdbuf();
	std::string vertexSource = vertexStream.str();

	if (vertexSource.empty())
	{
		std::cerr << "ERROR::SHADER::VERTEX_SHADER_READ_FAILURE\n" << std::endl;
	}

	fragmentFile.open(fragmentPath);
	fragmentStream << fragmentFile.rdbuf();
	std::string fragmentSource = fragmentStream.str();

	if (fragmentSource.empty())
	{
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER_READ_FAILURE\n" << std::endl;
	}

	const char* vShader = vertexSource.c_str();
	const char* fShader = fragmentSource.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vShader, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "ERROR::SHADER::VERTEX_SHADER_COMPILE_FAILURE\n" << infoLog << std::endl;
	}

	glShaderSource(fragment, 1, &fShader, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER_COMPILE_FAILURE\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cerr << "ERROR::SHADER::PROGRAM_LINK_FAILURE\n" << infoLog << std::endl;
	}

	glUseProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix4f(const std::string& name, const glm::mat4 matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}