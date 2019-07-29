#ifndef __Light_H__
#define __Light_H__

#include "GLApplication.h"
#include "Shader.h"
#include "Camera.h"

class Light : public GLApplication {
public:
	Light();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();
	virtual void cleanup();

	virtual void handle_input(GLFWwindow* window);
	virtual void handle_event(const Event& evt);

private:
	bool setup_buffer();

private:
	Camera _camera;

	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _light_vao;

	Shader _cube_shader;
	Shader _light_source_shader;

	float _last_time;
	bool _frist_press;

	float _last_mouse_x;
	float _last_mouse_y;
	bool _frist_move;
};

#endif //__Light_H__