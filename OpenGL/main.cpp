#include <iostream>
#include "Triangle.h"
#include "Texture.h"
#include "Transform.h"
#include "Enter3D.h"

int main(int argc, char** argv) {
	std::string title = "LearnOpenGL";
	GLBase* base = new Enter3D();
	base->init_gl_environment();
	if (base->create_window(800, 600, title, nullptr, nullptr)) {
		base->render();
		base->exit();
	}
	return 0;
}