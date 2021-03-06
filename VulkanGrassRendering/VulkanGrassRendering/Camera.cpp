#include "Camera.h"
#include <iostream>

#define GLM_FORCE_RADIANS
// Use Vulkan depth range of 0.0 to 1.0 instead of OpenGL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	r = 10.0f;
	theta = 0.0f;
	phi = 0.0f;
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projectionMatrix[1][1] *= -1; // y-coordinate is flipped
}

Camera::Camera(float aspectRatio) {
	r = 10.0f;
	theta = 0.0f;
	phi = 0.0f;
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	projectionMatrix[1][1] *= -1; // y-coordinate is flipped
}

void Camera::updateOrbit(double deltaX, double deltaY, double deltaZ) {
	theta += deltaX;
	phi += deltaY;
	r = glm::clamp(r - (float)deltaZ, 1.0f, 50.0f);

	float radTheta = glm::radians(theta);
	float radPhi = glm::radians(phi);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radTheta, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), radPhi, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 finalTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) * rotation * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, r));

	viewMatrix = glm::inverse(finalTransform);
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}