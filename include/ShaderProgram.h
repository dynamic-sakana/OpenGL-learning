#pragma once
#include "SnowyOwl.h"
#include "Texture2D.h"
#define MAX_TEXTURE_UNIT_ACCOUNT 32
class ShaderProgram {
public:
	/**
	 * @brief 构造一个Shader对象
	 * @param vsPath 顶点着色器文件位置
	 * @param fsPath 片元着色器文件位置
	 */
	ShaderProgram(const char* vsPath, const char* fsPath);

	/**
	 * @brief 析构Shader对象，删除program
	 */
	~ShaderProgram();

	/**
	 * @brief 设置shader program采样器采样的纹理来自于哪一个纹理对象
	 * @param name 采样器名称
	 * @param texture 新的纹理对象
	 */
	void SetTexture(const char* name, Texture2D* texture);

	/**
	 * @brief 告诉着色器程序如何解析VBO缓冲中的数据，使用前需绑定相应的VBO，这个函数是对glVertexAttributePinter函数的封装
	 * @param name 这个属性对应的着色器程序输入
	 * @param dimension 这个属性的维度
	 * @param type 这个属性的数据类型
	 * @param normalize 是否归一化
	 * @param stride 一个顶点的数据的步长
	 * @param offset 该属性对于一个顶点数据的偏移量
	 */
	inline void ParseVBOData(const char* name, int dimension, GLenum type, bool normalize, int stride, size_t offset);

	/**
	 * @brief 设置mat4类型的uniform变量
	 * @param name 该uniform变量的值
	 * @param transpose 是否转置
	 * @param value 要传入的矩阵
	 */
	inline void SetUniformM4(const char* name, bool transpose, const glm::mat4& value);

	/**
	 * @brief 获取该shader program的变量位置
	 * @param name 该变量的名称
	 * @return GLuint 该变量在shader program中的编号
	 */
	inline GLuint GetAttributeLocation(const char* name);

	/**
	 * @brief 获取该shader program的uniform变量位置
	 * @param name 该变量的名称
	 * @return GLuint 该变量在shader program中的编号
	 */
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
	bool unitAvailable[];
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