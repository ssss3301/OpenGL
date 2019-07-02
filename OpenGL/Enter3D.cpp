#include "Enter3D.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

void Enter3D::before_render() {
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[] = {
		3, 2, 1, 1, 3, 0
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(6 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	int width, height, channel;
	unsigned char* data = stbi_load("textures/wall.jpg", &width, &height, &channel, 0);
	if (data != nullptr)
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	stbi_image_free(data);

	shader_info shaders;
	shaders.vertex_shader = "shaders/enter3d.vert";
	shaders.fragment_shader = "shaders/enter3d.frag";
	shader_prog = load_shader(shaders);

	matModelLocation = glGetUniformLocation(shader_prog, "matModel");
	matViewLocation = glGetUniformLocation(shader_prog, "matView");
	matProjLocation = glGetUniformLocation(shader_prog, "matProj");
}

void Enter3D::after_render() {
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

void Enter3D::draw_scene() {
	if (!shader_prog)
		return;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(matModelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0f));
	glUniformMatrix4fv(matViewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	glUniformMatrix4fv(matProjLocation, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(shader_prog);
	glActiveTexture(GL_TEXTURE0);//默认是激活的
	glBindTexture(GL_TEXTURE_2D, tex);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}