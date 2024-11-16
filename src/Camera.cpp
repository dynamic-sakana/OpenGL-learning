#include "Camera.h"
#include "Log.h"
// 构造函数
Camera::Camera() :
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f) { UpdateVectors(); }

void Camera::SetPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Camera::SetRotation(float pitch, float yaw, float roll) {
	rotation = glm::vec3(pitch, yaw, roll);
	UpdateVectors();
}

void Camera::Translate(float x, float y, float z) {
	glm::vec3 offset = glm::vec3(x, y, z);
	position += offset.x * right + offset.y * up + offset.z * forward;
}

void Camera::Rotate(float pitch, float yaw, float roll) {
	rotation.x += pitch;
	rotation.y += yaw;
	rotation.z += roll;
	ClampRotation();
	UpdateVectors();
}

void Camera::UpdateVectors() {
	// 使用欧拉角计算前向量
	forward.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
	forward.y = sin(glm::radians(rotation.x));
	forward.z = -cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	forward = glm::normalize(forward);

	// 计算右向量和上向量
	right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, forward));
}

// 限制 rotation 范围
void Camera::ClampRotation() {
	for (int i = 0; i < 3; ++i) {
		if (rotation[i] > 180.0f) {
			rotation[i] -= 360.0f; // 保持在 [-180, 180]
		}
		if (rotation[i] < -180.0f) {
			rotation[i] += 360.0f;
		}
	}
}

glm::mat4 Camera::GetViewMat() {
	return glm::lookAt(position, position + forward, up);
}
