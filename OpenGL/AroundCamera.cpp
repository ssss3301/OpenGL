#include "AroundCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

void AroundCamera::render() {
	if (!shader_prog)
		return;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(matModelLocation, 1, GL_FALSE, glm::value_ptr(model));

	float radius = 3.0f;
	float camera_x = sin(glfwGetTime()) * radius;
	float camera_z = cos(glfwGetTime()) * radius;
	glm::vec3 camera_pos(camera_x, 0.0f, camera_z);
	glm::vec3 target_pos(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	
	glm::mat4 view = glm::lookAt(camera_pos, target_pos, up);
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