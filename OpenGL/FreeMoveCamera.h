#ifndef __FreeMoveCamera_H__
#define __FreeMoveCamera_H__

#include "Enter3D.h"
#include "glm/glm.hpp"

class FreeMoveCamera : public Enter3D
{
public:
	FreeMoveCamera();
	virtual void draw_scene();
	virtual void process_input(GLFWwindow* window);

private:
	float _last_time;
	glm::vec3 camera_pos;
	glm::vec3 direction;
	glm::vec3 up;
};

#endif//__FreeMoveCamera_H__