#ifndef __material_h__
#define __material_h__

#include "GLApplication.h"
#include "Shader.h"
#include "Camera.h"

class Material : public GLApplication{
public:
	Material();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();
	virtual void handle_input(GLFWwindow* window);
	virtual void handle_event(const Event& evt);

private:
	void setup_render_environment();

private:
	Shader	_shader;
	Camera	_cam;

	unsigned int _cube_vao;
	unsigned int _cube_vbo;

	float _last_time;
	bool _frist_press;

	float _last_mouse_x;
	float _last_mouse_y;
	bool _frist_move;
};

#endif //__material_h__