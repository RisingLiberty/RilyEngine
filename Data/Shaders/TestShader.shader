#shader vertex
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 mvp;

void main()
{
	vec4 pos = vec4(position, 1.0f);
	gl_Position = mvp * pos;
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}