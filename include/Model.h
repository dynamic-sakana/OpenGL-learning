#pragma once
#include "SnowyOwl.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include <vector>
#include <utility>
class Model {
public:
	/**
	 * @brief 构造一个模型类对象
	 * @param url 
	 */
	Model(const char* url);
	/**
	 * @brief 清除显存中的VBO和EBO数据
	 */
	~Model();

	/**
	 * @brief 设置要使用哪一个shader program来绘制这个模型
	 * @param shader 
	 */
	void SetShader(ShaderProgram* shader);

	/**
	 * @brief 设置shader program采样器采样的纹理来自于哪一个纹理对象
	 * @param name 采样器名称
	 * @param texture 新的纹理对象
	 */
	void SetTexture(const char* name, Texture2D* texture);

	/**
	 * @brief 在现在的基础上移动该模型（相对于世界坐标系）
	 * @param x x轴分量
	 * @param y y轴分量
	 * @param z z轴分量
	 */
	void Translate(float x, float y, float z);

	/**
	 * @brief 在现在的基础上移动该模型（相对于世界坐标系）
	 * @param displacement 位移
	 */
	void Translate(const glm::vec3& displacement);

	/**
	 * @brief 在现在的基础上移动该模型（相对于自身坐标系）
	 * @param x x轴分量
	 * @param y y轴分量
	 * @param z z轴分量
	 */
	void Move(float x, float y, float z);

	/**
	 * @brief 在现在的基础上移动该模型（相对于自身坐标系）
	 * @param displacement 位移
	 */
	void Move(const glm::vec3& displacement);

	/**
	 * @brief 在现在的基础上旋转该模型（相对于世界坐标系）
	 * @param angle 旋转角度（弧度制）
	 * @param x 旋转轴的x
	 * @param y 旋转轴的y
	 * @param z 旋转轴的z
	 */
	void Revolve(float angle, float x, float y, float z);

	/**
	 * @brief 在现在的基础上旋转该模型（相对于世界坐标系）
	 * @param angle 旋转角度（弧度制）
	 * @param axis 旋转轴
	 */
	void Revolve(float angle, const glm::vec3& axis);

	/**
	 * @brief 在现在的基础上旋转该模型（相对于自身坐标系）
	 * @param angle 旋转角度（弧度制）
	 * @param x 旋转轴的x
	 * @param y 旋转轴的y
	 * @param z 旋转轴的z
	 */
	void Rotate(float angle, float x, float y, float z);

	/**
	 * @brief 在现在的基础上旋转该模型（相对于自身坐标系）
	 * @param angle 旋转角度（弧度制）
	 * @param axis 旋转轴
	 */
	void Rotate(float angle, const glm::vec3& axis);

	/**
	 * @brief 在现在的基础上放缩该模型（相对于自身坐标系）
	 * @param x x方向上的倍率
	 * @param y y方向上的倍率
	 * @param z z方向上的倍率
	 */
	void Scale(float x, float y, float z);

	/**
	 * @brief 在现在的基础上放缩该模型（相对于自身坐标系）
	 * @param resize 各个方向的倍率
	 */
	void Scale(const glm::vec3& resize);

	/**
	 * @brief 使用这个模型的shader program绘制这个模型
	 * @param viewMat 视图矩阵
	 * @param projMat 投影矩阵
	 */
	void Draw(const glm::mat4& viewMat, const glm::mat4& projMat);

private:
	GLuint VBO;
	GLuint EBO;
	int count;	// EBO的个数（顶点的个数）

	/**
	 * @brief 模型矩阵，记录着这个模型的位置信息等
	 */
	glm::mat4 modelMat;

	/**
	 * @brief 渲染这个模型所使用的shader program，由于这个shader program不会在这个模型消失后也消失，所以不用在析构函数中清理
	 */
	ShaderProgram* shader = nullptr;
	/**
	 * @brief 这个模型使用的texuture列表，储存着着色器程序的采样行为：哪一个采样器采样哪一个纹理（一个采样器对应一个纹理对象）
	 */
	std::vector<std::pair<const char*, Texture2D*>> texture2DList;
};