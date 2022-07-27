#include "Texture.hpp"

#include "../stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture::Texture(const char* path)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);
	if (data)
	{
		GLenum mode;
		switch (m_channels)
		{
		case 4:
			mode = GL_RGBA;
			break;
		case 3:
			mode = GL_RGB;
			break;
		default:
			mode = GL_RGBA;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

unsigned int Texture::getWidth()
{
	return m_width;
}
unsigned int Texture::getHeight()
{
	return m_height;
}
unsigned int Texture::getID()
{
	return ID;
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}