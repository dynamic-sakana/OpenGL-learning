#version 460 core
in vec3 m_normal;
in vec2 m_textCoord;
uniform sampler2D sampler1;

out vec4 color;
void main() {
	color = vec4(texture(sampler1, m_textCoord).rgb + m_normal * 0.0001f, 1.0);
}