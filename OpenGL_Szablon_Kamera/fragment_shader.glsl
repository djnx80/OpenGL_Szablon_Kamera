#version 450

in vec2 wsp_tekstury;

uniform sampler2D moja_tekstura;
out vec4 kolor_wyjsciowy;

void main()
{ 
	vec4 texel = texture(moja_tekstura, wsp_tekstury);
	kolor_wyjsciowy = texel;
}