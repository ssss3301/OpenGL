#ifndef __LightingMap_H__
#define __LightingMap_H__

#include "GLApplication.h"
#include "Shader.h"
#include "Camera.h"

class LightingMap : public GLApplication{
public:
	LightingMap();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();

private:
	void setup_render_envrionment();

private:
	Camera _cam;
	Shader _shaderProg;
	unsigned int _vao;
	unsigned int _diffuse_map_tex;
	unsigned int _specular_map_tex;
};

#endif //__LightingMap_H__