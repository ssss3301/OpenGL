#ifndef __Enter3D_H__
#define __Enter3D_H__

#include "GLBase.h"

class Enter3D : public GLBase {
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
	virtual void before_render();
	virtual void after_render();
	virtual void draw_scene();

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