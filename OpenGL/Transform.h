#ifndef __Transform_H__
#define __Transform_H__

#include "GLApplication.h"

class Transform : public GLApplication {
public:
	Transform() {
		vao = 0;
		vbo = 0;
		ebo = 0;
		tex = 0;
		tex_location = -1;
		transform_mat_location = -1;
		shader_prog = 0;
	}
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();
	virtual void cleanup();

private:
	void setup_vao();
	void load_textures();
	void load_shaders();

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int tex;
	int tex_location;
	int transform_mat_location;
	unsigned int shader_prog;
};

#endif
