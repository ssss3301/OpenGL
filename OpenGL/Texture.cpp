#include "Texture.h"
#include "stb_image.h"
#include <glm/glm.hpp>

bool Texture::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}

	setup_vao();
	load_textures();
	load_shaders();

	return true;
}

void Texture::cleanup() {
	if (ebo != 0) {
		glDeleteBuffers(1, &ebo);
	}

	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
	}

	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
	}

	if (tex != 0) {
		glDeleteTextures(1, &tex);
	}

	if (prog != 0) {
		glDeleteProgram(prog);
	}
}

void Texture::render() {
	if (prog == 0) {
		return;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
 	glBindTexture(GL_TEXTURE_2D, tex);

/*	//多个纹理
	int location = glGetUniformLocation(prog, "tex");
	glUniform1i(location, 0); //设置纹理对应的纹理单元
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);*/

	glUseProgram(prog);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Texture::setup_vao() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(6 * sizeof(vertices[0])));
	glEnableVertexAttribArray(2);

	unsigned int indices[] = {
		3, 2, 1, 1, 3, 0
	};

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Texture::load_textures() {
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channel;
	unsigned char* data = stbi_load("textures/wall.jpg", &width, &height, &channel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load_shaders() {
	shader_file_info shaders;
	shaders.vertex_shader = "shaders/tex.vert";
	shaders.fragment_shader = "shaders/tex.frag";
	prog = load_shader_from_file(shaders);
}