#ifndef __Transform_H__
#define __Transform_H__

#include "GLBase.h"

class Transform : public GLBase {
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
	virtual void before_render();
	virtual void after_render();
	virtual void draw_scene();

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
