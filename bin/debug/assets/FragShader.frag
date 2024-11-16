#version 460 core
in vec3 m_color;
in vec2 m_uv;
uniform sampler2D sampler1;

out vec4 color;
void main() {
	color = vec4(texture(sampler1, m_uv).rgb + m_color * 0.0001f, 1.0);
}