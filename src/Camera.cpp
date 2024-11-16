#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() {
}

void Camera::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::SetRotation(float pitch, float yaw, float roll) {
	rotation.x = pitch;
	rotation.y = yaw;
	rotation.z = roll;

	// x = cos(pitch) * sin(yaw);
	// y = sin(pitch);
	// z = cos(pitch) * cos(yaw);
	forward.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	forward.y = sin(glm::radians(pitch));
	forward.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	forward = glm::normalize(forward);
}

void Camera::Translate(float x, float y, float z) {
	position += forward * z;
	position += glm::cross(forward, up) * x;
	position += up * y;
}

void Camera::Rotate(float pitch, float yaw, float roll) {
	SetRotation(rotation.x + pitch, rotation.y + yaw, rotation.z + roll);
}

glm::mat4 Camera::GetViewMat() {
	return glm::lookAt(position, position + forward, up);
}
