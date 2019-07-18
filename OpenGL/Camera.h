#ifndef __Camera_H__
#define __Camera_H__

#include "glm/gtx/transform.hpp"

class Camera {
public:
	typedef enum CameraMoveDirection {
		Right,
		Left,
		Forward,
		Backward
	};

public:
	Camera(glm::vec3 camera_positon, glm::vec3 worldup, glm::vec3 front = glm::vec3(0.0, 0.0, -1.0f), float pitch = 0.0f, float yaw = -90.0f);
	Camera(float xpos, float ypos, float zpos, float x_worldup, float y_worldup, float z_worldup
		, float front_x = 0.0f, float front_y = 0.0f, float front_z = -1.0f, float pitch = 0.0f, float yaw = -90.0f);

	glm::mat4 get_view_matrix() const;
	void set_max_zoom(float max_zoom);
	void set_sensitivity(float sensitivity);
	void set_movespeed(float speed);

	void process_keyboard(CameraMoveDirection direction, float delta_time);
	void process_mouse_move(double xoffset, double yoffset);
	void process_scroll(double yoffset);

	float zoom() const;

private:
	void update_camera();

private:
	glm::vec3 _position;
	glm::vec3 _worldup;
	glm::vec3 _right;
	glm::vec3 _front;
	glm::vec3 _up;

	float _pitch;
	float _yaw;
	float _zoom;
	float _max_zoom;
	float _sensitivity;
	float _movespeed;
};

#endif//__Camera_H__