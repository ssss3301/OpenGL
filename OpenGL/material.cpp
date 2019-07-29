#include "material.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

Material::Material() : _cam(glm::vec3(0.0, 0.0, 3.0f)){
	_frist_press = true;
	_frist_move = true;
}


bool Material::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}
	
	_shader.init_with_shader_file("shaders/material.vert", "shaders/material.frag");
	setup_render_environment();
	return true;
}

void Material::render() {
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	_shader.use();
	_shader.set_uniform_matrix4fv("model_mat", value_ptr(glm::mat4(1.0f)));
	_shader.set_uniform_matrix4fv("view_mat", value_ptr(_cam.get_view_matrix()));
	glm::mat4 projMat = glm::perspective(glm::radians(_cam.zoom()), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	_shader.set_uniform_matrix4fv("proj_mat", value_ptr(projMat));
	_shader.set_uniform3f("mat.ambient", 1.0f, 0.5f, 0.31f);
	_shader.set_uniform3f("mat.diffuse", 1.0f, 0.5f, 0.31f);
	_shader.set_uniform3f("mat.specular", 0.5f, 0.5f, 0.5f);
	_shader.set_uniform1f("mat.shininess", 32);

	glm::vec3 lightcolor;
	lightcolor.x = sin(glfwGetTime() * 2.0f);
	lightcolor.y = sin(glfwGetTime() * 0.7f);
	lightcolor.z = sin(glfwGetTime() * 1.3f);
	glm::vec3 diffuse_color = lightcolor * glm::vec3(0.5f);
	glm::vec3 ambient_color = lightcolor * glm::vec3(0.2f);
	_shader.set_uniform3fv("l.diffuse", value_ptr(diffuse_color));
	_shader.set_uniform3fv("l.ambinet", value_ptr(ambient_color));
	_shader.set_uniform3f("l.specular", 1.0, 1.0, 1.0);
	_shader.set_uniform3f("l.position", 0.0f, 0.0f, 2.0f);
	_shader.set_uniform3fv("viewPos", value_ptr(_cam.position()));
	
	glBindVertexArray(_cube_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Material::setup_render_environment() {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

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
	glGenVertexArrays(1, &_cube_vao);
	glBindVertexArray(_cube_vao);
	glGenBuffers(1, &_cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Material::handle_input(GLFWwindow* window) {
	if (_frist_press) {
		_last_time = glfwGetTime();
		_frist_press = false;
	}
	float current = glfwGetTime();
	float delta_time = current - _last_time;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_cam.process_keyboard(Camera::Forward, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		_cam.process_keyboard(Camera::Backward, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		_cam.process_keyboard(Camera::Right, delta_time);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		_cam.process_keyboard(Camera::Left, delta_time);
	}
	else {
		GLApplication::handle_input(window);
	}

	_last_time = current;
}

void Material::handle_event(const Event& evt) {
	switch (evt._type)
	{
	case Event::MouseMoved:
		if (_frist_move) {
			_last_mouse_x = evt._mousemove.xpos;
			_last_mouse_y = evt._mousemove.ypos;
			_frist_move = false;
		}
		_cam.process_mouse_move(evt._mousemove.xpos - _last_mouse_x, _last_mouse_y - evt._mousemove.ypos);
		_last_mouse_x = evt._mousemove.xpos;
		_last_mouse_y = evt._mousemove.ypos;
		break;
	case Event::MouseScroll:
		_cam.process_scroll(evt._mousescroll.yoffset);
		break;
	default:
		break;
	}
}
