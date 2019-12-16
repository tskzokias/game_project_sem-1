#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec2 in_TexCoord;

out vec3 ex_Color;
out vec2 TexCoord;

uniform mat4 Model;  // model matrix
uniform mat4 projection;

void main()
{
	//gl_Position = projection * Model * vec4(in_Position.xyz, 1.0f);
	gl_Position =  projection * Model * vec4(in_Position.xyz, 1.0f);
	ex_Color = in_Color;
	TexCoord = vec2(in_TexCoord.x, in_TexCoord.y);
}