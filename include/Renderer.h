#pragma once
#include "SnowyOwl.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Model.h"

class Camera;
class Renderer {
public:
	Renderer(HWND handle, int width, int height);
	~Renderer();

	void Resize(int newWidth, int newHeight);

	void InitializeGL();

	void Render();

	/**
	 * @brief 根据frameInterval的时间决定要移动多少个单位
	 * @param frameInterval 帧间隔
	 */
	void CameraMove(float frameInterval);

	/**
	 * @brief 这后面的函数都是设置Renderer按键状态的函数
	 */
	void WhenKeyPress(int keyNo);

	void WhenKeyLoose(int keyNo);

	void WhenMouseClick(int keyNo);

	void WhenMouseLoose(int keyNo);
	
	void WhenMouseMove(int currentX, int currentY);

private:
	bool CreateGLContext();
	/**
	 * @return float 返回这次调用这个函数到上次调用这个函数之间所经历的时间
	 */
	float GetFrameInterval();
private:
	HDC deviceContext;		// 设备上下文
	HGLRC renderContext;	// OpenGL渲染上下文
	HWND handle;			// 窗口句柄
	ShaderProgram* program;	// 着色器程序
	ShaderProgram* program2;
	Camera* camera;			// 摄像机
	Texture2D* text;		// 纹理
	Texture2D* text2;
	Model* model;			// 模型
	Model* model2;
	int width, height;		// 窗口的长和宽
	// 键盘事件
	bool w_pressed = false, s_pressed = false, a_pressed = false, d_pressed = false, q_pressed = false, e_pressed = false;
	// 鼠标点击
	bool lclicked = false, mclicked = false, rclicked = false;
	// 鼠标移动
	int mouseMoveX = 0, mouseMoveY = 0;
	// 鼠标灵敏度
	float rotateSpeed = 0.1f;
	// 摄像机速度
	float cameraSpeed = 4.0f;
};