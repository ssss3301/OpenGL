#include "Triangle.h"
#include <iostream>

#define USE_INDEX_ELEMENT

bool Triangle::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}

	setup_vao();
	load_shaders();

	return true;
}


void Triangle::setup_vao() {
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

#ifdef USE_INDEX_ELEMENT
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif

	glBindVertexArray(0);

}

void Triangle::load_shaders() {
	shader_file_info info;
	info.vertex_shader = "shaders/triangle.vert";
	info.fragment_shader = "shaders/triangle.frag";
	shader_prog = load_shader_from_file(info);
}


void Triangle::cleanup() {
	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
	}

	if (ebo != 0) {
		glDeleteBuffers(1, &ebo);
	}

	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
	}

	if (shader_prog != 0) {
		glDeleteProgram(shader_prog);
	}
}


void Triangle::render() {
	if (shader_prog == 0) {
		return;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_prog);
	glBindVertexArray(vao);
#ifdef USE_INDEX_ELEMENT
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
#else
	glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
}
