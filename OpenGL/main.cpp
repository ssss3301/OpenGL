#include <iostream>
#include "Triangle.h"
#include "Texture.h"
#include "Transform.h"
#include "Enter3D.h"
#include "AroundCamera.h"
#include "FreeMoveCamera.h"
#include "Event.h"
#include "Light.h"
#include "material.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Event evt;
	evt._type = Event::MouseMoved;
	evt._mousemove.xpos = xpos;
	evt._mousemove.ypos = ypos;
	EventManager::GetInstance()->pushEvent(evt);
}

void frame_size_change_callback(GLFWwindow* window, int width, int height) {
	Event evt;
	evt._type = Event::Resized;
	evt._size.width = width;
	evt._size.height = height;
	EventManager::GetInstance()->pushEvent(evt);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Event evt;
	evt._type = Event::MouseScroll;
	evt._mousescroll.xoffset = xoffset;
	evt._mousescroll.yoffset = yoffset;
	EventManager::GetInstance()->pushEvent(evt);
}

int main(int argc, char** argv) {
	std::string title = "LearnOpenGL";
	GLApplication* app = new Material();
	if (app->init(800, 600, title, nullptr, nullptr)) {
		app->set_framebuffer_size_callback(frame_size_change_callback);
		app->set_mouse_callback(mouse_callback);
		app->set_mouse_scroll_callback(scroll_callback);
		app->runLoop();
		app->exit();
	}
	return 0;
}