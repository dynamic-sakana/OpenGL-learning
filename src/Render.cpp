#include "SnowyOwl.h"
#include "Renderer.h"
#include <chrono>
Renderer::Renderer(HWND handle, int width, int height) {
	this->handle = handle;
	this->width = width;
	this->height = height;

	CreateGLContext();
	wglMakeCurrent(deviceContext, renderContext);
	CALL(glewInit());

	CALL(glViewport(0, 0, width, height));
	program = new ShaderProgram("assets/VertShader.vert", "assets/FragShader.frag");
	camera = new Camera();
	this->InitializeGL();
}

Renderer::~Renderer() {
	wglMakeCurrent(NULL, NULL);
	if (renderContext)
		wglDeleteContext(renderContext);
	if (deviceContext)
		ReleaseDC(handle, deviceContext);
}

bool Renderer::CreateGLContext() {
	deviceContext = GetDC(handle);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	// 结构体版本号，指定为1
	pfd.nVersion = 1;
	// 颜色有几位RGBA，共32位
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;	// 设置深度缓冲位深
	pfd.cStencilBits = 8;	// 设置模板缓冲区位深
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int format = ChoosePixelFormat(deviceContext, &pfd);
	if (format == 0) {
		throw;
		return false;
	}

	SetPixelFormat(deviceContext, format, &pfd);
	renderContext = wglCreateContext(deviceContext);

	return true;
}

void Renderer::Resize(int newWidth, int newHeight) {
	CALL(glViewport(0, 0, newWidth, newHeight));
}

void Renderer::InitializeGL() {
	smp1 = program->GetUniformLocation("smp1");

	// 将vert中的数据移到显存中，使用VAO监视并记录VBO中的数据
	CALL(glGenVertexArrays(1, &VAO));
	CALL(glBindVertexArray(VAO));
	VBO = Util::CreateGLBuffer(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	program->ParseVBOData("pos", 3, GL_FLOAT, false, 8 * sizeof(float), 0);
	program->ParseVBOData("color", 3, GL_FLOAT, false, 8 * sizeof(float), 3 * sizeof(float));
	program->ParseVBOData("uv", 2, GL_FLOAT, false, 8 * sizeof(float), 6 * sizeof(float));

	// 解绑VAO和VBO
	CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	CALL(glBindVertexArray(0));

	CALL(glGenTextures(1, &text1));
	CALL(glBindTexture(GL_TEXTURE_2D, text1));
	// 设置环绕方式
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	// 设置过滤方式
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	Image text("assets/text.jpg");

	CALL(glTexImage2D(
		GL_TEXTURE_2D,	// 纹理类型
		0,				// mipmap等级
		GL_RGBA, 		// 纹理的格式
		text.width,
		text.height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		text.data
	));
	CALL(glGenerateMipmap(GL_TEXTURE_2D));

	CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::Render() {

	CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));					// 设置背景颜色
	CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));	// 清理颜色缓冲、深度缓冲

	program->Apply();

	CALL(glActiveTexture(GL_TEXTURE0));
	CALL(glBindTexture(GL_TEXTURE_2D, text1));
	CALL(glUniform1i(smp1, 0));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 view = camera->GetViewMat();

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	program->SetUniformM4("modelMat", false, model);
	program->SetUniformM4("viewMat", false, view);
	program->SetUniformM4("projMat", false, proj);

	CALL(glBindVertexArray(VAO));
	CALL(glDrawArrays(GL_QUADS, 0, 4));							// 绘制VAO

	double frameInterval = GetFrameInterval();
	if (w_pressed)
		camera->Translate(0, 0, cameraSpeed * frameInterval);
	if (s_pressed)
		camera->Translate(0, 0, - cameraSpeed * frameInterval);
	if (a_pressed)
		camera->Translate(-cameraSpeed * frameInterval, 0, 0);
	if (d_pressed)
		camera->Translate(cameraSpeed * frameInterval, 0, 0);
	if (e_pressed)
		camera->Translate(0, cameraSpeed * frameInterval, 0);
	if (q_pressed)
		camera->Translate(0, -cameraSpeed * frameInterval, 0);

	// if ((mouseMoveX || mouseMoveY) && lclicked) {
	// 	camera->Rotate(mouseMoveY * rotateSpeed, mouseMoveX * rotateSpeed);
	// }
	camera->Rotate(0.02, 0);

	SwapBuffers(deviceContext);
}

void Renderer::WhenKeyPress(int keyNo) {
	switch (keyNo) {
	case 'W':
		w_pressed = true;
		break;
	case 'A':
		a_pressed = true;
		break;
	case 'S':
		s_pressed = true;
		break;
	case 'D':
		d_pressed = true;
		break;
	case 'Q':
		q_pressed = true;
		break;
	case 'E':
		e_pressed = true;
		break;
	}
}

void Renderer::WhenKeyLoose(int keyNo) {
	switch (keyNo) {
	case 'W':
		w_pressed = false;
		break;
	case 'A':
		a_pressed = false;
		break;
	case 'S':
		s_pressed = false;
		break;
	case 'D':
		d_pressed = false;
		break;
	case 'Q':
		q_pressed = false;
		break;
	case 'E':
		e_pressed = false;
		break;
	}
}

void Renderer::WhenMouseClick(int keyNo) {
	switch (keyNo)
	{
	case WM_LBUTTONDOWN:
		lclicked = true;
		break;
	case WM_MBUTTONDOWN:
		mclicked = true;
		break;
	case WM_RBUTTONDOWN:
		rclicked = true;
		break;
	}
}

void Renderer::WhenMouseLoose(int keyNo) {
	switch (keyNo) {
	case WM_LBUTTONUP:
		lclicked = false;
		break;
	case WM_MBUTTONUP:
		mclicked = false;
		break;
	case WM_RBUTTONUP:
		rclicked = false;
		break;
	}
}

void Renderer::WhenMouseMove(int currentX, int currentY) {
	static int initX = currentX, initY = currentY;
	mouseMoveX = currentX - initX;
	mouseMoveY = currentY - initY;
	initX = currentX;
	initY = currentY;
}

double Renderer::GetFrameInterval() {
	static int64_t last_time = 0;
	if (last_time == 0) {
		auto begin = std::chrono::system_clock::now();
		last_time = std::chrono::duration_cast<std::chrono::milliseconds>(begin.time_since_epoch()).count();
	}
	auto now = std::chrono::system_clock::now();
	int64_t now_time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	int64_t delta_time = now_time - last_time;
	last_time = now_time;

	return (float)delta_time / 1000;
}
