#ifndef FrameBuffer_H
#define FrameBuffer_H

#include "GLApplication.h"
#include "Shader.h"
#include "Camera.h"

class FrameBufferApplication : public GLApplication {
public:
	FrameBufferApplication();
	~FrameBufferApplication();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();

private:
	void setup_render_environment();

private:
	unsigned int _boxVAO;
	unsigned int _boxVBO;
	unsigned int _boxTex;
	unsigned int _floorVAO;
	unsigned int _floorVBO;
	unsigned int _floorTex;
	unsigned int _quadVAO;
	unsigned int _quadVBO;
	unsigned int _colorTex;

	unsigned int _rbo;
	unsigned int _fbo;

	Shader _boxAndFloorShader;
	Camera _cam;
	Shader _quadShader;
};

#endif //FrameBuffer_H