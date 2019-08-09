#ifndef LoadModel_H
#define LoadModel_H

#include "GLApplication.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class LoadModel : public GLApplication {
public:
	LoadModel();
	~LoadModel();
	bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();

private:
	Shader _shader;
	Model* _model;
	Camera _cam;
};

#endif //LoadModel_H