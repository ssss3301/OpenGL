#include "Shader.h"
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <iostream>

Shader::Shader() :_shaderProg(0), _vert_shader(0), _frag_shader(0){

}

Shader::Shader(const std::string& vert_shader_file, const std::string& frag_shader_file) 
	: _shaderProg(0), _vert_shader(0), _frag_shader(0) {
	init_with_shader_file(vert_shader_file, frag_shader_file);
}

Shader::Shader(const char* vert_shader, const char* frag_shader)
	: _shaderProg(0) , _vert_shader(0), _frag_shader(0){
	init_with_shader_string(vert_shader, frag_shader);
}

Shader::~Shader() {
	if (_vert_shader != 0) {
		glDeleteShader(_vert_shader);
	}
	
	if (_frag_shader != 0) {
		glDeleteShader(_frag_shader);
	}

	if (_shaderProg != 0) {
		glDeleteProgram(_shaderProg);
	}
}


void Shader::init_with_shader_file(const std::string& vert_shader_file, const std::string& frag_shader_file) {
	std::string vert_shader_string = get_file_content(vert_shader_file);
	std::string frag_shader_string = get_file_content(frag_shader_file);
	init_with_shader_string(vert_shader_string.c_str(), frag_shader_string.c_str());
}

void Shader::init_with_shader_string(const char* vert_shader, const char* frag_shader) {
	_shaderProg = glCreateProgram();
	if (_shaderProg == 0) {
		return;
	}

	int success = 0;

	_vert_shader = glCreateShader(GL_VERTEX_SHADER);
	if (_vert_shader == 0) {
		return;
	}
	glShaderSource(_vert_shader, 1, &vert_shader, nullptr);
	glCompileShader(_vert_shader);
	glGetShaderiv(_vert_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		int info_len = 0;
		glGetShaderiv(_vert_shader, GL_INFO_LOG_LENGTH, &info_len);
		char* info_buffer = new char[info_len + 1];
		glGetShaderInfoLog(_vert_shader, info_len, &info_len, info_buffer);
		info_buffer[info_len] = '\0';
		std::cout << info_buffer << std::endl;
		delete[] info_buffer;
		return;
	}

	_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (_frag_shader == 0) {
		return;
	}
	glShaderSource(_frag_shader, 1, &frag_shader, nullptr);
	glCompileShader(_frag_shader);
	glGetShaderiv(_frag_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		int info_len = 0;
		glGetShaderiv(_frag_shader, GL_INFO_LOG_LENGTH, &info_len);
		char* info_buffer = new char[info_len + 1];
		glGetShaderInfoLog(_frag_shader, info_len, &info_len, info_buffer);
		info_buffer[info_len] = '\0';
		std::cout << info_buffer << std::endl;
		delete[] info_buffer;
		return;
	}

	glAttachShader(_shaderProg, _vert_shader);
	glAttachShader(_shaderProg, _frag_shader);
	glLinkProgram(_shaderProg);
	glGetProgramiv(_shaderProg, GL_LINK_STATUS, &success);
	if (!success) {
		int link_info_len = 0;
		glGetProgramiv(_shaderProg, GL_INFO_LOG_LENGTH, &link_info_len);
		char* link_info_buffer = new char[link_info_len + 1];
		glGetProgramInfoLog(_shaderProg, link_info_len, &link_info_len, link_info_buffer);
		link_info_buffer[link_info_len] = '\0';
		std::cout << link_info_buffer << std::endl;
		delete[] link_info_buffer;
		return;
	}
}

void Shader::use() {
	if (_shaderProg > 0) {
		glUseProgram(_shaderProg);
	}
}

void Shader::set_uniform1i(const std::string& uniform_name, int value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1i(location, value);
	}
}

void Shader::set_uniform1ui(const std::string& uniform_name, unsigned int value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1ui(location, value);
	}
}

void Shader::set_uniform1iv(const std::string& uniform_name, const int* value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1iv(location, 1, value);
	}
}

void Shader::set_uniform1uiv(const std::string& uniform_name, const unsigned int* value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1uiv(_shaderProg, 1, value);
	}
}

void Shader::set_uniform1f(const std::string& uniform_name, float value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1f(location, value);
	}
}

void Shader::set_unfiorm1fv(const std::string& uniform_name, const float* value) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform1fv(location, 1, value);
	}
}

void Shader::set_uniform2i(const std::string& uniform_name, int v0, int v1) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2i(location, v0, v1);
	}
}

void Shader::set_uniform2ui(const std::string& uniform_name, unsigned int v0, unsigned int v1) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2ui(location, v0, v1);
	}
}

void Shader::set_uniform2iv(const std::string& uniform_name, const int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2iv(_shaderProg, 2, v);
	}
}

void Shader::set_uniform2uiv(const std::string& uniform_name, const unsigned int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2uiv(location, 2, v);
	}
}

void Shader::set_uniform2f(const std::string& uniform_name, float v0, float v1) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2f(location, v0, v1);
	}
}

void Shader::set_uniform2fv(const std::string& uniform_name, const float* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform2fv(location, 2, v);
	}
}

void Shader::set_uniform3i(const std::string& uniform_name, int v0, int v1, int v2) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3i(location, v0, v1, v2);
	}
}

void Shader::set_uniform3ui(const std::string& uniform_name, unsigned int v0, unsigned int v1, unsigned int v2) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3ui(location, v0, v1, v2);
	}
}

void Shader::set_uniform3iv(const std::string& uniform_name, const int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3iv(location, 3, v);
	}
}

void Shader::set_uniform3uiv(const std::string& uniform_name, const unsigned int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3uiv(location, 3, v);
	}
}

void Shader::set_uniform3f(const std::string& uniform_name, float v0, float v1, float v2) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3f(location, v0, v1, v2);
	}
}

void Shader::set_uniform3fv(const std::string& uniform_name, const float* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform3fv(location, 3, v);
	}
}

void Shader::set_uniform4i(const std::string& uniform_name, int v0, int v1, int v2, int v3) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4i(location, v0, v1, v2, v3);
	}
}

void Shader::set_uniform4ui(const std::string& uniform_name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4ui(location, v0, v1, v2, v3);
	}
}

void Shader::set_uniform4iv(const std::string& uniform_name, const int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4iv(location, 4, v);
	}
}

void Shader::set_uniform4uiv(const std::string& uniform_name, const unsigned int* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4uiv(location, 4, v);
	}
}

void Shader::set_uniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4f(location, v0, v1, v2, v3);
	}
}

void Shader::set_uniform4fv(const std::string& uniform_name, const float* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniform4fv(location, 4, v);
	}
}

void Shader::set_uniform_matrix4fv(const std::string uniform_name, const float* v) {
	int location = glGetUniformLocation(_shaderProg, uniform_name.c_str());
	if (location >= 0) {
		glUniformMatrix4fv(location, 1, GL_FALSE, v);
	}
}

std::string Shader::get_file_content(const std::string file) {
	std::ifstream file_stream(file);
	if (!file_stream.is_open()) {
		throw std::runtime_error("Unable to open file: " + file);
	}

	std::stringstream stream;
	stream << file_stream.rdbuf();
	return stream.str();
}