#include "Triangle.h"
#include <iostream>

void Triangle::before_render() {
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	shader_info info;
	info.vertex_shader = "shaders/triangle.vert";
	info.fragment_shader = "shaders/triangle.frag";
	shader_prog = load_shader(info);
}

void Triangle::after_render() {
	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
	}

	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
	}

	if (shader_prog != 0) {
		glDeleteProgram(shader_prog);
	}
}


void Triangle::draw_scene() {
	if (shader_prog == 0) {
		return;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_prog);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}