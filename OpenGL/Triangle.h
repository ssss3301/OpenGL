#ifndef __Triangle_H__
#define __Triangle_H__

#include "GLApplication.h"

class Triangle : public GLApplication {
public:
	Triangle() : shader_prog(0), vao(0), vbo(0), ebo(0) {

	}
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
 	virtual void render();
	virtual void cleanup();

private:
	void setup_vao();
	void load_shaders();

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shader_prog;
};

#endif //__Triangle_H__