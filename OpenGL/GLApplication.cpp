#include "GLApplication.h"
#include <iostream>

bool GLApplication::init_gl_environment() {
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

bool GLApplication::init(int width, int height, std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (!init_gl_environment()) {
		return false;
	}

	_window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
	if (!_window) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return false;
	}
	_screen_width = width;
	_screen_height = height;

	return true;
}

void GLApplication::runLoop() {
	while (!glfwWindowShouldClose(_window)) {
		handle_input(_window);
		dispatch_event();
		before_render();
		render();
		after_render();
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void GLApplication::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLApplication::set_framebuffer_size_callback(GLFWframebuffersizefun callback) {
	if (_window) {
		glfwSetFramebufferSizeCallback(_window, callback);
	}
}

void GLApplication::handle_input(GLFWwindow* window) {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}

void GLApplication::dispatch_event() {
	Event evt;
	if (EventManager::GetInstance()->pollEvent(evt)) {
		handle_event(evt);
	}
}

void GLApplication::exit(){
	cleanup();
	glfwTerminate();
}

unsigned int GLApplication::load_shader_from_file(const shader_file_info& shader) {
	unsigned int prog = glCreateProgram();
	if (prog == 0)
		return 0;

	unsigned int vert_shader = compile_shader(shader.vertex_shader, GL_VERTEX_SHADER);
	unsigned int frag_shader = compile_shader(shader.fragment_shader, GL_FRAGMENT_SHADER);
	if (!vert_shader || !frag_shader) {
		return 0;
	}

	glAttachShader(prog, vert_shader);
	glAttachShader(prog, frag_shader);
	glLinkProgram(prog);

	int success;
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success) {
		int info_len = 0;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &info_len);
		char* info_buffer = new char[info_len];
		glGetProgramInfoLog(prog, info_len, NULL, info_buffer);
		std::cout << info_buffer << std::endl;
		delete[] info_buffer;
		return 0;
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return prog;
}

unsigned int GLApplication::compile_shader(const std::string& shader_file, int shader_type) {
	char source_buffer[1024] = { 0 };
	if (!read_shader_source(source_buffer, 1024, shader_file)) {
		return 0;
	}

	unsigned int shader;
	shader = glCreateShader(shader_type);
	if (shader == 0) {
		return 0;
	}

	char* source[] = { source_buffer };

	glShaderSource(shader, 1, source, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		int info_len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
		char* info = new char[info_len];
		glGetShaderInfoLog(shader, info_len, NULL, info);
		std::cout << info << std::endl;
		delete[] info;
		return 0;
	}

	return shader;
}

bool GLApplication::read_shader_source(char* source_buffer, int max_buffer_len, const std::string& shader_file) {
	FILE* file = fopen(shader_file.c_str(), "r+");
	if (file == nullptr) {
		return false;
	}

	fseek(file, 0, SEEK_END);
	int file_length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (file_length > max_buffer_len) {
		fclose(file);
		return false;
	}

	int left_bytes = file_length;
	while (left_bytes > 0) {
		int read_bytes = fread(source_buffer + file_length - left_bytes, 1, left_bytes, file);
		if(feof(file))
			break;
		left_bytes -= read_bytes;
	}

	fclose(file);
	return true;
}

void GLApplication::before_render() {

}

void GLApplication::after_render() {

}


void GLApplication::use_wireframe_mode(bool use) {
	_use_wireframe_mode = use;
	if (_use_wireframe_mode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void GLApplication::set_input_mode(int mode, int value){
	if (_window) {
		glfwSetInputMode(_window, mode, value);
	}
}

void GLApplication::set_mouse_callback(GLFWcursorposfun callback) {
	if (_window) {
		glfwSetCursorPosCallback(_window, callback);
	}
}

bool GLApplication::is_wireframe_mode() const {
	return _use_wireframe_mode;
}

void GLApplication::cleanup() {

}

void GLApplication::handle_event(const Event& evt) {

}

void GLApplication::set_mouse_scroll_callback(GLFWscrollfun callback) {
	if (_window) {
		glfwSetScrollCallback(_window, callback);
	}
}
