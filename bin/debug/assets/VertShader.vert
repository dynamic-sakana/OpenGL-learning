// 顶点着色器
#version 460 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

uniform mat4 modelMat;	// 模型变换矩阵
uniform mat4 viewMat;	// 视口变换矩阵
uniform mat4 projMat;	// 透视变换矩阵

out vec3 m_color;
out vec2 m_uv;

void main() {
	gl_Position = projMat * viewMat * modelMat * vec4(pos, 1.0);
	// gl_Position = vec4(pos, 1.0);
	m_color = color;
	m_uv = uv;
}