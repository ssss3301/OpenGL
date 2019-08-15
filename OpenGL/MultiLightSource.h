#ifndef __MultiLightSource_H__
#define __MultiLightSource_H__

#include "GLApplication.h"
#include "Camera.h"
#include "Shader.h"

class MultiLightSource : public GLApplication {
public:
	MultiLightSource();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();

private:
	void setup_vao();
	void load_textures();

private:
	Camera _cam;
	Shader _shaderProg;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _diffuseTex;
	unsigned int _specularTex;
};

#endif //__MultiLightSource_H__