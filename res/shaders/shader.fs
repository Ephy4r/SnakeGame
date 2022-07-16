#version 460 core
in vec3 ourColor;
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, texCoords) * vec4(ourColor, 1.0);
}