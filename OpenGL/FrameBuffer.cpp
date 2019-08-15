#include "FrameBuffer.h"
#include "stb_image.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

FrameBufferApplication::FrameBufferApplication() : _cam(glm::vec3(0.0, 0.0, 5.0f)){
	_boxVAO = 0;
	_boxVBO = 0;
	_boxTex = 0;
	_floorVAO = 0;
	_floorVBO  =  0;
	_floorTex = 0;
	_quadVAO = 0;
	_quadVBO  = 0;
	_colorTex =  0;
}

FrameBufferApplication::~FrameBufferApplication() {

}

bool FrameBufferApplication::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}
	setup_render_environment();
	_boxAndFloorShader.init_with_shader_file("shaders/box_floor.vert", "shaders/box_floor.frag");
	_quadShader.init_with_shader_file("shaders/quad.vert", "shaders/quad.frag");
	return true;
}

void FrameBufferApplication::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	_boxAndFloorShader.use();
	glm::mat4 model(1.0f);
	_boxAndFloorShader.set_uniform_matrix4fv("model_mat", glm::value_ptr(model));
	_boxAndFloorShader.set_uniform_matrix4fv("view_mat", glm::value_ptr(_cam.get_view_matrix()));
	glm::mat4 perspective_mat = glm::perspective(glm::radians(_cam.zoom()), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	_boxAndFloorShader.set_uniform_matrix4fv("proj_mat", glm::value_ptr(perspective_mat));
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _boxTex);
	glBindVertexArray(_boxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, _floorTex);
	glBindVertexArray(_floorVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	_quadShader.use();
	glBindVertexArray(_quadVAO);
	glBindTexture(GL_TEXTURE_2D, _colorTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBufferApplication::setup_render_environment() {
	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	float planeVertices[] = {
		// positions          // texture Coords 
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	glGenVertexArrays(1, &_boxVAO);
	glBindVertexArray(_boxVAO);
	glGenBuffers(1, &_boxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _boxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(cubeVertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(cubeVertices[0]), (void*)(3 * sizeof(cubeVertices[0])));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &_floorVAO);
	glBindVertexArray(_floorVAO);
	glGenBuffers(1, &_floorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(planeVertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(planeVertices[0]), (void*)(3 * sizeof(cubeVertices[0])));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	int width, height, channel;
	unsigned char* box_img_data = stbi_load("textures/marble.jpg", &width, &height, &channel, 0);
	if (box_img_data) {
		glGenTextures(1, &_boxTex);
		glBindTexture(GL_TEXTURE_2D, _boxTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, box_img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(box_img_data);
	}

	unsigned char* floor_img_data = stbi_load("textures/metal.png", &width, &height, &channel, 0);
	if (floor_img_data) {
		glGenTextures(1, &_floorTex);
		glBindTexture(GL_TEXTURE_2D, _floorTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, floor_img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(floor_img_data);
	}

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &_quadVAO);
	glBindVertexArray(_quadVAO);
	glGenBuffers(1, &_quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(quadVertices[0]), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(quadVertices[0]), (void*)(2 * sizeof(quadVertices[0])));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glGenTextures(1, &_colorTex);
	glBindTexture(GL_TEXTURE_2D, _colorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screen_width, _screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _screen_width, _screen_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTex, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
	if (!glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
