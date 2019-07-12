#ifndef __Enter3D_H__
#define __Enter3D_H__

#include "GLApplication.h"

class Enter3D : public GLApplication {
public:
	Enter3D() { 
		vao = 0;
		vbo = 0;
		ebo = 0;
		shader_prog = 0;
		matModelLocation = -1;
		matViewLocation = -1;
		matProjLocation = -1;
		tex = 0;
	}
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void cleanup();
	virtual void render();

private:
	void setup_vao();
	void load_textures();
	void load_shaders();

protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int tex;
	unsigned int shader_prog;

	int matModelLocation;
	int matViewLocation;
	int matProjLocation;
};

#endif //__Enter3D_H__