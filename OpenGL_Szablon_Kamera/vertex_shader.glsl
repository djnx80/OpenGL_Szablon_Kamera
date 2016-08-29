#version 450

layout(location = 0) in vec3 pozycja;
layout(location = 2) in vec2 vt;

uniform mat4 macierz_przesuniecia;
uniform mat4 view_matrix;
uniform mat4 perspective_matrix;

out vec2 wsp_tekstury;

void main()
{
	wsp_tekstury = vt;
	gl_Position = perspective_matrix * view_matrix * macierz_przesuniecia*vec4(pozycja, 1.0);
}

//macierz_przesuniecia*vec4(pozycja, 1.0);