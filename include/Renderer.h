#pragma once

#include "SnowyOwl.h"
#include <Windows.h>
#include <GL/glew.h>

namespace SnowyOwl {
	class Renderer {
	public:
		Renderer(HWND handle, int width, int height);
		~Renderer();

		void Resize(int newWidth, int newHeight);

		void Render();

	private:
		
		bool CreateGLContext();

	private:
		HDC deviceContext;
		HGLRC renderContext;
		HWND handle;
	};
}