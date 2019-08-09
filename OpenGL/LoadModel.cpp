#include "LoadModel.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

LoadModel::LoadModel() : _cam(glm::vec3(0.0, 0.0, 3.0)){

}

LoadModel::~LoadModel() {
	delete _model;
}

bool LoadModel::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!GLApplication::init(width, height, title, monitor, share)) {
		return false;
	}

	_model = new Model("models/nanosuit.obj");
	_shader.init_with_shader_file("shaders/simple_model.vert", "shaders/simple_model.frag");
}

void LoadModel::render() {
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	_shader.use();
	glm::mat4 proj_mat4 = glm::perspective(glm::radians(_cam.zoom()), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	glm::mat4 view_mat4 = _cam.get_view_matrix();
	glm::mat4 model_mat4(1.0f);
	model_mat4 = glm::translate(model_mat4, glm::vec3(0.0f, -1.75f, 0.0f));
	model_mat4 = glm::scale(model_mat4, glm::vec3(0.2f, 0.2f, 0.2f));
	_shader.set_uniform_matrix4fv("proj_mat", glm::value_ptr(proj_mat4));
	_shader.set_uniform_matrix4fv("model_mat", glm::value_ptr(model_mat4));
	_shader.set_uniform_matrix4fv("view_mat", glm::value_ptr(view_mat4));
	_model->Draw(_shader);
}
