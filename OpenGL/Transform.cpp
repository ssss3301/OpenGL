#include "Transform.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

void Transform::before_render() {
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int indices[] = {
		3, 2, 1, 1, 3, 0
	};
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	int width, height, channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("textures/awesomeface.png", &width, &height, &channel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	shader_info shaders;
	shaders.vertex_shader = "shaders/transform.vert";
	shaders.fragment_shader = "shaders/transform.frag";
	shader_prog = load_shader(shaders);
	tex_location = glGetUniformLocation(shader_prog, "tex");
	transform_mat_location = glGetUniformLocation(shader_prog, "trans_mat");
}

void Transform::after_render() {
	if (ebo != 0) {
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}

	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (tex != 0) {
		glDeleteTextures(1, &tex);
		tex = 0;
	}

	if (shader_prog != 0) {
		glDeleteProgram(shader_prog);
		shader_prog = 0;
	}
}

void Transform::draw_scene() {
	if (shader_prog == 0) {
		return;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.f, 0.f, 1.0));
	if (transform_mat_location != -1) {
		glUniformMatrix4fv(transform_mat_location, 1, GL_FALSE, glm::value_ptr(trans));
	}

	if (tex_location != -1) {
		glUniform1i(tex_location, 0);
	}
	glUseProgram(shader_prog);

	glBindVertexArray(vao);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}