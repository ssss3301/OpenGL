#ifndef __Shader_H__
#define __Shader_H__

#include <string>

class Shader {
public:
	Shader();
	Shader(const std::string& vert_shader_file, const std::string& frag_shader_file);
	Shader(const char* vert_shader, const char* frag_shader);
	~Shader();

	void init_with_shader_file(const std::string& vert_shader_file, const std::string& frag_shader_file);
	void init_with_shader_string(const char* vert_shader, const char* frag_shader);

	void use();

	void set_uniform1i(const std::string& uniform_name, int value);
	void set_uniform1ui(const std::string& uniform_name, unsigned int value);
	void set_uniform1iv(const std::string& uniform_name, const int* value);
	void set_uniform1uiv(const std::string& uniform_name, const unsigned int* value);
	void set_uniform1f(const std::string& uniform_name, float value);
	void set_unfiorm1fv(const std::string& uniform_name, const float* value);

	void set_uniform2i(const std::string& uniform_name, int v0, int v1);
	void set_uniform2ui(const std::string& uniform_name, unsigned int v0, unsigned int v1);
	void set_uniform2iv(const std::string& uniform_name, const int* v);
	void set_uniform2uiv(const std::string& uniform_name, const unsigned int* v);
	void set_uniform2f(const std::string& uniform_name, float v0, float v1);
	void set_uniform2fv(const std::string& uniform_name, const float* v);
	
	void set_uniform3i(const std::string& uniform_name, int v0, int v1, int v2);
	void set_uniform3ui(const std::string& uniform_name, unsigned int v0, unsigned int v1, unsigned int v2);
	void set_uniform3iv(const std::string& uniform_name, const int* v);
	void set_uniform3uiv(const std::string& uniform_name, const unsigned int* v);
	void set_uniform3f(const std::string& uniform_name, float v0, float v1, float v2);
	void set_uniform3fv(const std::string& uniform_name, const float* v);

	void set_uniform4i(const std::string& uniform_name, int v0, int v1, int v2, int v3);
	void set_uniform4ui(const std::string& uniform_name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
	void set_uniform4iv(const std::string& uniform_name, const int* v);
	void set_uniform4uiv(const std::string& uniform_name, const unsigned int* v);
	void set_uniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);
	void set_uniform4fv(const std::string& uniform_name, const float* v);

	void set_uniform_matrix4fv(const std::string uniform_name, const float* v);

private:
	std::string get_file_content(const std::string file);

public:
	unsigned  int _shaderProg;
	unsigned int _vert_shader;
	unsigned int _frag_shader;
};

#endif //__Shader_H__
