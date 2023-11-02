#include <zpch.h>
#include "Shader.h"

namespace Zewada {

	Shader::Shader(const char* path)
		: m_path(path)
	{
		//m_path will be shit cause assetpool
		m_shaderID = Load();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glEnable(GL_BLEND);
		Enable();
		int ids[16];
		for (int i = 0; i < 16; i++)
		{
			ids[i] = i;
		}
		SetUniform1iv("textures", ids, 16);
		Disable();
	}

	Shader::~Shader() {
		glDeleteProgram(m_shaderID);
	}

	GLuint Shader::Load() {
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string source = FileUtils::read_file(m_path);
		unsigned int size = source.find("//SPLIT");
		std::string vertSourceString = source.substr(0, size);
		std::string fragSourceString = source.substr(size + 7, source.length());

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		GLint result;

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile frament shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::GetUniformLocation(const GLchar* name) {
		return glGetUniformLocation(m_shaderID, name);
	}

	void Shader::SetUniform1f(const GLchar* name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, float* value, int count)
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int* value, int count)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const glm::vec2 Vector) {
		glUniform2f(GetUniformLocation(name), Vector.x, Vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const glm::vec3 Vector) {
		glUniform3f(GetUniformLocation(name), Vector.x, Vector.y, Vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const glm::vec4 Vector) {
		glUniform4f(GetUniformLocation(name), Vector.x, Vector.y, Vector.z, Vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const glm::mat4& Matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void Shader::Enable() const {
		glUseProgram(m_shaderID);
	}

	void Shader::Disable() const {
		glUseProgram(0);
	}

}