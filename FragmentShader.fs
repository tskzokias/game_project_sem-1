#version 330 core
 
in vec3 ex_Color; 
out vec4 out_Color; 
in vec2 TexCoord;

uniform sampler2D texture1;
uniform int mode;
 
void main ()  
{  
	//if(mode == 0)
		out_Color = texture(texture1, TexCoord); 
	//else 
		//out_Color = vec4(ex_Color, 1.0);
}  