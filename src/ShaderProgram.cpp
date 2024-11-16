#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vsPath, const char* fsPath) {
	GLuint vs = this->CompileShader(GL_VERTEX_SHADER, vsPath);
	GLuint fs = this->CompileShader(GL_FRAGMENT_SHADER, fsPath);

	CALL(program = glCreateProgram());

	CALL(glAttachShader(program, vs));
	CALL(glAttachShader(program, fs));

	CALL(glLinkProgram(program));
	GLint success = GL_TRUE;
	CALL(glGetProgramiv(program, GL_LINK_STATUS, &success));
	if (!success) {
		char infoLog[1024];
		GLsizei logLen = 0;
		CALL(glGetShaderInfoLog(program, sizeof(infoLog), &logLen, infoLog));
		std::string error;
		error.append("Error linking shader:\n").append(infoLog);
		MessageBoxA(0, error.c_str(), "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);
		CALL(glDeleteProgram(program));

		ERROR_LOG("Shader linking error.");

		throw "Shader Fault.";
	}
	CALL(glDetachShader(program, vs));
	CALL(glDetachShader(program, fs));
	CALL(glDeleteShader(vs));
	CALL(glDeleteShader(fs));
}

ShaderProgram::~ShaderProgram() {
	CALL(glDeleteProgram(program));
}

void ShaderProgram::Apply() {
	CALL(glUseProgram(program));
}

void ShaderProgram::Stop() {
	CALL(glUseProgram(0));
}

inline GLuint ShaderProgram::CompileShader(GLenum shaderType, const char* shaderPath) {
	char* src = Util::LoadFileContent(shaderPath);
	GLuint shader = glCreateShader(shaderType);
	CALL(glShaderSource(shader, 1, &src, NULL));
	CALL(glCompileShader(shader));
	GLint success = GL_TRUE;
	CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success) {
		char infoLog[1024];
		GLsizei logLen = 0;
		CALL(glGetShaderInfoLog(shader, sizeof(infoLog), &logLen, infoLog));
		std::string error("Error compiling shader:\n");
		error.append(infoLog);
		MessageBoxA(0, error.c_str(), "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);

		ERROR_LOG("Shader compiling error.");

		CALL(glDeleteShader(shader));
		throw;
	}
	delete src;
	return shader;
}
