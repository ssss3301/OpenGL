#include "Light.h"
#include "stb_image.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

Light::Light() 
	: _camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0, 1.0f, 0.0)){
	_vao = 0;
	_vbo = 0;
	_light_vao = 0;
	_frist_press = true;
	_frist_move = true;
}

bool Light::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}

	if (!setup_buffer() ) {
		return false;
	}

	_cube_shader.init_with_shader_file("shaders/simple_light.vert", "shaders/simple_light.frag");
	_light_source_shader.init_with_shader_file("shaders/simple_light.vert", "shaders/light_source.frag");

	return true;
}

void Light::render() {
	glClearColor(0.1, 0.1, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 model_mat(1.0f);
	
	glm::mat4 view_mat = _camera.get_view_matrix();

	glm::mat4 proj_mat(1.0f);
	proj_mat = glm::perspective(glm::radians(_camera.zoom()), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);

	_cube_shader.use();
	_cube_shader.set_uniform_matrix4fv("model_mat", value_ptr(model_mat));
	_cube_shader.set_uniform_matrix4fv("view_mat", value_ptr(view_mat));
	_cube_shader.set_uniform_matrix4fv("proj_mat", value_ptr(proj_mat));
	_cube_shader.set_uniform3f("light_color", 1.0f, 1.0f, 1.0f);
	_cube_shader.set_uniform3f("object_color", 1.0f, 0.5f, 0.31f);
	_cube_shader.set_uniform3f("light_pos", 0.5, 0, 2.0f);
	_cube_shader.set_uniform3f("viewPos", 0.0f, 0.0f, 3.0f);

	glBindVertexArray(_vbo);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::mat4 light_model_mat(1.0f);
	light_model_mat = glm::translate(light_model_mat, glm::vec3(1.2f, 1.0f, -2.0f));
	light_model_mat = glm::scale(light_model_mat, glm::vec3(0.5f));
	_light_source_shader.use();
	_light_source_shader.set_uniform_matrix4fv("model_mat", value_ptr(light_model_mat));
	_light_source_shader.set_uniform_matrix4fv("view_mat", value_ptr(view_mat));
	_light_source_shader.set_uniform_matrix4fv("proj_mat", value_ptr(proj_mat));
	glBindVertexArray(_light_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

bool Light::setup_buffer() {
	float vertices[] = {
	 -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &_vao);
	if (_vao == 0) {
		return false;
	}
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	if (_vao == 0) {
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &_vao);
		return false;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &_light_vao);
	glBindVertexArray(_light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return true;
}

void Light::cleanup() {
	if (_vao != 0) {
		glDeleteVertexArrays(1, &_vao);
	}
	if (_vbo != 0) {
		glDeleteBuffers(1, &_vbo);
	}
	if (_light_vao != 0) {
		glDeleteVertexArrays(1, &_light_vao);
	}
}

void Light::handle_input(GLFWwindow* window) {
	if (_frist_press) {
		_last_time = glfwGetTime();
		_frist_press = false;
	}
	float current = glfwGetTime();
	float delta_time = current - _last_time;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_camera.process_keyboard(Camera::Forward, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		_camera.process_keyboard(Camera::Backward, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		_camera.process_keyboard(Camera::Right, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		_camera.process_keyboard(Camera::Left, delta_time);
	}
	else {
		GLApplication::handle_input(window);
	}

	_last_time = current;
}

void Light::handle_event(const Event& evt) {
	switch (evt._type)
	{
	case Event::MouseMoved:
		if (_frist_move) {
			_last_mouse_x = evt._mousemove.xpos;
			_last_mouse_y = evt._mousemove.ypos;
			_frist_move = false;
		}
		_camera.process_mouse_move(evt._mousemove.xpos - _last_mouse_x, _last_mouse_y - evt._mousemove.ypos);
		_last_mouse_x = evt._mousemove.xpos;
		_last_mouse_y = evt._mousemove.ypos;
		break;
	case Event::MouseScroll:
		_camera.process_scroll(evt._mousescroll.yoffset);
		break;
	default:
		break;
	}
}

