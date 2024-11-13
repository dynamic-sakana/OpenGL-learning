#include "Renderer.h"
#include <assert.h>

using namespace SnowyOwl;

Renderer::Renderer(HWND handle, int width, int height) {
	this->handle = handle;
	CreateGLContext();
	wglMakeCurrent(deviceContext, renderContext);
	assert(glewInit() == GLEW_OK);

	glViewport(0, 0, width, height);
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

void Renderer::Render() {
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SwapBuffers(deviceContext);
}

void Renderer::Resize(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}