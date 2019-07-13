#ifndef __Texture_H__
#define __Texture_H__

#include "GLApplication.h"

class Texture : public GLApplication {
public:
	Texture() {
		vao = 0;
		vbo = 0;
		ebo = 0;
		tex = 0;
		prog = 0;
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
	unsigned int prog;
};

#endif//__Texture_H__