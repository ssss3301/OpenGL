#ifndef __FreeMoveCamera_H__
#define __FreeMoveCamera_H__

#include "Enter3D.h"
#include "glm/glm.hpp"

class FreeMoveCamera : public Enter3D
{
public:
	FreeMoveCamera();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();
	virtual void handle_input(GLFWwindow* window);
	virtual void handle_event(const Event& evt);

private:
	void on_size_changed(int width, int height);
	void on_mouse_moved(double xpos, double ypos);
	void on_mouse_scroll(double xoffset, double yoffset);

private:
	float _last_time;
	glm::vec3 camera_pos;
	glm::vec3 direction;
	glm::vec3 up;

	double _lastx;
	double _lasty;
	float _pitch;
	float _yaw;
	float _fov;

	bool firstMouse;
};

#endif//__FreeMoveCamera_H__