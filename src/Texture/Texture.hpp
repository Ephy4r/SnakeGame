#pragma once

#include <iostream>

class Texture
{
private:
	int m_width;
	int m_height;
	int m_channels;
	unsigned int ID;
public:
	Texture(const char* path);
	
	void bind();
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getID();
};