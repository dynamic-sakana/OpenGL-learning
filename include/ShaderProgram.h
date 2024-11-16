#pragma once
#include "SnowyOwl.h"

class ShaderProgram {
public:
	/**
	 * @brief 构造一个Shader对象
	 * @param vsPath 顶点着色器文件位置
	 * @param fsPath 片元着色器文件位置
	 */
	ShaderProgram(const char* vsPath, const char* fsPath);
	ShaderProgram() = default;

	/**
	 * @brief 析构Shader对象，删除program
	 */
	~ShaderProgram();

	/**
	 * @brief 告诉着色器程序如何解析VBO缓冲中的数据，使用前需绑定相应的VBO
	 * @param name 这个属性对应的着色器程序输入
	 * @param dimension 这个属性的维度
	 * @param type 这个属性的数据类型
	 * @param normalize 是否归一化
	 * @param stride 一个顶点的数据的步长
	 * @param offset 该属性对于一个顶点数据的偏移量
	 */
	inline void ParseVBOData(const char* name, int dimension, GLenum type, bool normalize, int stride, size_t offset);

	inline void SetUniformM4(const char* name, bool transpose, const glm::mat4& value);
	inline GLuint GetAttributeLocation(const char* name);
	inline GLuint GetUniformLocation(const char* name);

	/**
	 * @brief 启用这个Shader
	 */
	void Apply();

	/**
	 * @brief 禁用这个Shader
	 */
	void Stop();
private:
	inline GLuint CompileShader(GLenum shaderType, const char* shaderPath);

	GLuint program;
};

inline void ShaderProgram::ParseVBOData(const char* name, int dimension, GLenum type, bool normalize, int stride, size_t offset) {
	GLint location = this->GetAttributeLocation(name);
	CALL(glEnableVertexAttribArray(location));
	CALL(glVertexAttribPointer(
		location,
		dimension,
		type,
		(GLint)normalize,
		stride,
		(void*)offset
	));
}

inline void ShaderProgram::SetUniformM4(const char* name, bool transpose, const glm::mat4& value) {
	GLint location = this->GetUniformLocation(name);
	CALL(glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value)));
}

inline GLuint ShaderProgram::GetAttributeLocation(const char* name) {
	CALL(GLuint result = glGetAttribLocation(program, name));
	return result;
}

inline GLuint ShaderProgram::GetUniformLocation(const char* name) {
	CALL(GLuint result = glGetUniformLocation(program, name));
	return result;
}