#pragma once

#include <iostream>
#include <Vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../../../Utils/Resource/FileUtils.h"

namespace Zewada {		
	class Shader {
	private:
		GLuint m_shaderID;
		const char* m_path;
	public:
		Shader(const char* path);
		~Shader();

		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, float* value, int count);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int* value, int count);
		void SetUniform2f(const GLchar* name, const glm::vec2 Vector);
		void SetUniform3f(const GLchar* name, const glm::vec3 Vector);
		void SetUniform4f(const GLchar* name, const glm::vec4 Vector);
		void SetUniformMat4(const GLchar* name, const glm::mat4& Matrix);

		void Enable() const;
		void Disable() const;
	private:
		GLuint Load();
		GLint GetUniformLocation(const GLchar* name);
	};

}
