#pragma once

#include "SnowyOwl.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture2D.h"
class ShaderProgram;
class Camera;
class Renderer {
public:
	Renderer(HWND handle, int width, int height);
	~Renderer();

	void Resize(int newWidth, int newHeight);

	void InitializeGL();

	void Render();

	void WhenKeyPress(int keyNo);

	void WhenKeyLoose(int keyNo);

	void WhenMouseClick(int keyNo);

	void WhenMouseLoose(int keyNo);
	
	void WhenMouseMove(int currentX, int currentY);

	double GetFrameInterval();

private:
	bool CreateGLContext();

private:
	HDC deviceContext;
	HGLRC renderContext;
	HWND handle;
	ShaderProgram* program;
	Camera* camera;
	Mesh* mesh;
	Texture2D* text;
	GLuint VBO, VAO, smp1, EBO;
	int width, height;
	// 键盘事件
	bool w_pressed = false, s_pressed = false, a_pressed = false, d_pressed = false, q_pressed = false, e_pressed = false;
	// 鼠标点击
	bool lclicked = false, mclicked = false, rclicked = false;
	// 鼠标移动
	int mouseMoveX = 0, mouseMoveY = 0;
	float rotateSpeed = 0.2f;

	float cameraSpeed = 4.0f;
};