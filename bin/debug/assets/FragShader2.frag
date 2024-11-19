#version 460 core
in vec3 m_normal;
in vec2 m_textCoord;
uniform sampler2D sampler1;

out vec4 color;
void main() {
	color = vec4(mix(texture(sampler1, m_textCoord).rgb, m_normal, 0.0001), 1.0) * 0.001 + vec4(m_normal, 1.0);
}