#pragma once
#include "SnowyOwl.h"
class Camera {
public:
	Camera();
	~Camera() = default;

	/**
	 * @brief 设置这台摄像机的位置
	 */
	void SetPosition(float x, float y, float z);

	/**
	 * @brief 设置这台摄像机的偏转，单位：角度
	 * 
	 * @param pitch 上下俯仰角
	 * @param yaw 左右偏航角
	 * @param roll 左右翻滚角，默认0
	 */
	void SetRotation(float pitch, float yaw, float roll = 0);

	/**
	 * @brief 在原来的位置上移动(x,y,z)
	 */
	void Translate(float x, float y, float z);

	/**
	 * @brief 在原来的基础上旋转，单位：角度
	 *
	 * @param pitch 上下俯仰角
	 * @param yaw 左右偏航角
	 * @param roll 左右翻滚角，默认0
	 */
	void Rotate(float pitch, float yaw, float roll = 0);

	/**
	 * @brief 获取视角矩阵
	 * @return 视角矩阵
	 */
	glm::mat4 GetViewMat();

private:

	void UpdateVectors();
	void ClampRotation();
	glm::vec3 position;
	glm::vec3 rotation;
	
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right; // 新增右向量
};