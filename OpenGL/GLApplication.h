#ifndef __GL_BASE_H__
#define __GL_BASE_H__

#include <glad/glad.h>
#include <glfw3.h>

#include <string>
#include "Event.h"

typedef struct shader_file_info {
	std::string vertex_shader;
	std::string fragment_shader;
};

class GLApplication {
public:
	GLApplication() : _window(nullptr), _use_wireframe_mode(false) 
	{

	}
	virtual ~GLApplication() {}

public:
	virtual bool init_gl_environment();
	virtual bool init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	virtual void runLoop();

	virtual void render();
	virtual void before_render();
	virtual void after_render();

	virtual void handle_input(GLFWwindow* window);
	virtual void handle_event(const Event& evt);


	void use_wireframe_mode(bool use);
	void set_input_mode(int mode, int value);
	bool is_wireframe_mode() const;

	unsigned int load_shader_from_file(const shader_file_info& shader);

	virtual void cleanup();
	virtual void exit();

public:
	void set_framebuffer_size_callback(GLFWframebuffersizefun callback);
	void set_mouse_callback(GLFWcursorposfun callback);
	void set_mouse_scroll_callback(GLFWscrollfun callback);

private:
	unsigned int compile_shader(const std::string& shader_file, int shader_type);
	void dispatch_event();

private:
	bool read_shader_source(char* source_buffer, int max_buffer_len, const std::string& shader_file);

protected:
	GLFWwindow* _window;
	bool		_use_wireframe_mode;
	int			_screen_width;
	int			_screen_height;
};


#endif //__GL_BASE_H__