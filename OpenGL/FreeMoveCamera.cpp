#include "FreeMoveCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

FreeMoveCamera::FreeMoveCamera() {
	_last_time = glfwGetTime();
	camera_pos = glm::vec3(0.0, 0.0, 3.0f);
	direction = glm::vec3(0.0, 0.0, -1.0f);
	up = glm::vec3(0.0, 1.0, 0.0);
}

void FreeMoveCamera::render() {
	if (!shader_prog)
		return;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 view = glm::lookAt(camera_pos, camera_pos + direction, up);
	glUniformMatrix4fv(matViewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(_fov), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	glUniformMatrix4fv(matProjLocation, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(shader_prog);
	glActiveTexture(GL_TEXTURE0);//默认是激活的
	glBindTexture(GL_TEXTURE_2D, tex);
	glBindVertexArray(vao);
	for (int i = 0; i < 10; ++i) {
		glm::mat4 model(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(matModelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}

void FreeMoveCamera::handle_input(GLFWwindow* window) {
	float current_time = glfwGetTime();
	float delta_time = current_time - _last_time;
	float camera_speed = 0.25 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_pos += direction * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera_pos -= direction * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera_pos -= glm::normalize(glm::cross(direction, up)) * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera_pos += glm::normalize(glm::cross(direction, up)) * camera_speed;
	}

	_last_time = current_time;

	Enter3D::handle_input(window);
}

bool FreeMoveCamera::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!Enter3D::init(width, height, title, monitor, share)) {
		return false;
	}
	set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_lastx = width / 2.0f;
	_lasty = height / 2.0f;
	_pitch = 0.0f;
	_yaw = -90.0f;
	_fov = 45.0f;
	firstMouse = true;

	return true;
}

void FreeMoveCamera::handle_event(const Event& evt) {
	switch (evt._type)
	{
	case Event::Resized:
		on_size_changed(evt._size.width, evt._size.height);
		break;

	case Event::MouseMoved:
		on_mouse_moved(evt._mousemove.xpos, evt._mousemove.ypos);
		break;

	case Event::MouseScroll:
		on_mouse_scroll(evt._mousescroll.xoffset, evt._mousescroll.yoffset);
		break;

	default:
		Enter3D::handle_event(evt);
		break;
	}
}

void FreeMoveCamera::on_size_changed(int width, int height) {
	glViewport(0, 0, width, height);
	_screen_width = width;
	_screen_height = height;
}

void FreeMoveCamera::on_mouse_moved(double xpos, double ypos) {
	if (firstMouse)
	{
		_lastx = xpos;
		_lasty = ypos;
		firstMouse = false;
	}

	float offset_x = xpos - _lastx;
	float offset_y = _lasty - ypos;

	float sensitivity = 0.05f;
	offset_x *= sensitivity;
	offset_y *= sensitivity;

	_pitch += offset_y;
	_yaw += offset_x;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction = glm::normalize(front);

	_lastx = xpos;
	_lasty = ypos;

}

void FreeMoveCamera::on_mouse_scroll(double xoffset, double yoffset) {
	if (_fov >= 1.0 && _fov <= 45.0f) {
		_fov -= yoffset;
	}

	if (_fov < 1.0f)
		_fov = 1.0f;
	if (_fov > 45.0f)
		_fov = 45.0f;
}
