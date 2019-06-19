#ifndef __Triangle_H__
#define __Triangle_H__

#include "GLBase.h"

class Triangle : public GLBase {
public:
	Triangle() : shader_prog(0), vao(0), vbo(0) {

	}
	virtual void before_render();
 	virtual void draw_scene();
	virtual void after_render();

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int shader_prog;
};

#endif //__Triangle_H__