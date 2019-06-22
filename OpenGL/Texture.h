#ifndef __Texture_H__
#define __Texture_H__

#include "GLBase.h"

class Texture : public GLBase {
public:
	Texture() {
		vao = 0;
		vbo = 0;
		ebo = 0;
		tex = 0;
		prog = 0;
	}
	virtual void before_render();
	virtual void draw_scene();
	virtual void after_render();

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int tex;
	unsigned int prog;
};

#endif//__Texture_H__