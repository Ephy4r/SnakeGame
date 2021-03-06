#version 460 core
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.5);
}