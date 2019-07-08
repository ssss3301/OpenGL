#include "FreeMoveCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

FreeMoveCamera::FreeMoveCamera() {
	_last_time = glfwGetTime();
	camera_pos = glm::vec3(0.0, 0.0, 3.0f);
	direction = glm::vec3(0.0, 0.0, -1.0f);
	up = glm::vec3(0.0, 1.0, 0.0);
}

void FreeMoveCamera::draw_scene() {
	if (!shader_prog)
		return;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(matModelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(camera_pos, camera_pos + direction, up);
	glUniformMatrix4fv(matViewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), _screen_width * 1.0f / _screen_height, 0.1f, 100.0f);
	glUniformMatrix4fv(matProjLocation, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(shader_prog);
	glActiveTexture(GL_TEXTURE0);//默认是激活的
	glBindTexture(GL_TEXTURE_2D, tex);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

}

void FreeMoveCamera::process_input(GLFWwindow* window) {
	float current_time = glfwGetTime();
	float delta_time = current_time - _last_time;
	float camera_speed = 0.25 * delta_time;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_pos += direction * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera_pos -= direction * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera_pos -= glm::normalize(glm::cross(direction, up)) * camera_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera_pos += glm::normalize(glm::cross(direction, up)) * camera_speed;
	}

	_last_time = current_time;
}
