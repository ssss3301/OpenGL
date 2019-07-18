#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 camera_positon, glm::vec3 worldup, glm::vec3 front, float pitch, float yaw) {
	_position = camera_positon;
	_worldup = worldup;
	_front = front;
	_pitch = pitch;
	_yaw = yaw;

	_movespeed = 2.5f;
	_sensitivity = 0.1f;
	_zoom = 45.0f;
	_max_zoom = 45.0f;

	update_camera();
}

Camera::Camera(float xpos, float ypos, float zpos, float x_worldup, float y_worldup, float z_worldup
	, float front_x, float front_y, float front_z, float pitch, float yaw) {
	_position = glm::vec3(xpos, ypos, zpos);
	_worldup = glm::vec3(x_worldup, y_worldup, z_worldup);
	_front = glm::vec3(front_x, front_y, front_z);
	_pitch = pitch;
	_yaw = yaw;
	_movespeed = 2.5f;
	_sensitivity = 0.1f;
	_zoom = 45.0f;
	update_camera();
}

glm::mat4 Camera::get_view_matrix() const {
	return glm::lookAt(_position, _position + _front, _up);
}

void Camera::set_max_zoom(float max_zoom) {
	_max_zoom = max_zoom;
}

void Camera::set_sensitivity(float sensitivity) {
	_sensitivity = sensitivity;
}

void Camera::set_movespeed(float speed) {
	_movespeed = speed;
}

void Camera::update_camera() {
	glm::vec3 camera_front;
	camera_front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	camera_front.y = sin(glm::radians(_pitch));
	camera_front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	_front = glm::normalize(camera_front);

	_right = glm::normalize(glm::cross(_front, _worldup));
	_up = glm::normalize(glm::cross(_right, _front));
	
}

void Camera::process_keyboard(CameraMoveDirection direction, float delta_time) {
	switch (direction)
	{
	case Camera::Right:
		_position.x += delta_time * _movespeed;
		break;
	case Camera::Left:
		_position.x -= delta_time * _movespeed;
		break;
	case Camera::Forward:
		_position.z -= delta_time * _movespeed;
		break;
	case Camera::Backward:
		_position.z += delta_time * _movespeed;
		break;
	default:
		break;
	}

	update_camera();
}

void Camera::process_mouse_move(double xoffset, double yoffset) {
	_yaw += xoffset * _sensitivity;
	_pitch += yoffset * _sensitivity;
	if (_pitch < -89.0f) {
		_pitch = -89.0f;
	}
	if (_pitch > 89.0f) {
		_pitch = 89.0f;
	}

	update_camera();
}

void Camera::process_scroll(double yoffset) {
	_zoom -= yoffset;
	if (_zoom >= _max_zoom) {
		_zoom = _max_zoom;
	}

	if (_zoom <= 1.0f)
		_zoom = 1.0f;
}

float Camera::zoom() const {
	return _zoom;
}
