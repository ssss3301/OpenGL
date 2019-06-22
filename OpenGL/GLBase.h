#ifndef __GL_BASE_H__
#define __GL_BASE_H__

#include <glad/glad.h>
#include <glfw3.h>

#include <string>

typedef struct shader_info {
	std::string vertex_shader;
	std::string fragment_shader;
};

class GLBase {
public:
	GLBase() : _window(nullptr), _use_wireframe_mode(false) {}
	virtual ~GLBase() {}
public:
	virtual bool init_gl_environment();
	virtual bool create_window(int width, int heigt, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void render();
	virtual void draw_scene();
	virtual void process_input(GLFWwindow* window);
	virtual void exit();
	virtual unsigned int load_shader(const shader_info& shader);
	virtual void before_render();
	virtual void after_render();
	virtual void before_draw_scene();
	virtual void after_draw_scene();

	void set_framebuffer_size_callback(GLFWframebuffersizefun callback);
	void use_wireframe_mode(bool use);

private:
	unsigned int compile_shader(const std::string& shader_file, int shader_type);

private:
	bool read_shader_source(char* source_buffer, int max_buffer_len, const std::string& shader_file);

private:
	GLFWwindow* _window;
	bool		_use_wireframe_mode;
};


#endif //__GL_BASE_H__