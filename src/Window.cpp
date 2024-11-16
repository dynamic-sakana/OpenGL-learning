#include "SnowyOwl.h"

Window::Window(HINSTANCE hInstance, STRING windowClass) {
	this->hInstance = hInstance;
	this->windowClass = STRING(windowClass.begin(), windowClass.end());
	RegisterWindowsClass();
}

Window::~Window() {
	bool sccucessfullyUnregister = UnregisterClass(this->windowClass.c_str(), hInstance);
	if (!sccucessfullyUnregister) {
		PopMessageBox(CONTEXT("出错啦"), CONTEXT("错误"), MB_OK | MB_ICONERROR);
	}
}

bool Window::RegisterWindowsClass() {
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// 窗口样式
	wcex.lpfnWndProc = HandleMessageSetUp;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.hIconSm = nullptr;
	wcex.lpszClassName = this->windowClass.c_str();
	if (!RegisterClassEx(&wcex)) {
		throw GetLastError();
		return false;
	}
	else {
		return true;
	}
}

bool Window::Initialize(STRING windowTitle, int width, int height, int nCmdShow) {
	this->windowTitle = windowTitle;
	this->width = width;
	this->height = height;
	int nWindMetricsX = GetSystemMetrics(SM_CXSCREEN);
	int nWindMetricsY = GetSystemMetrics(SM_CYSCREEN);
	RECT wr;
	wr.left = (nWindMetricsX - width) / 2;
	wr.top = (nWindMetricsY - height) / 2;
	wr.right = wr.left + width;
	wr.bottom = wr.top + height;
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	handle = CreateWindowEx(0,
		this->windowClass.c_str(),	// 窗口类名
		this->windowTitle.c_str(),	// 窗口标题
		WS_OVERLAPPEDWINDOW,		// 设置为这个就会有最大化最小化等等
		wr.left,					// 窗口左边的偏移量（单位像素）
		wr.top,						// 窗口右边的偏移量（单位像素）
		wr.right - wr.left,			// 窗口宽度（单位像素）
		wr.bottom - wr.top,			// 窗口高度（单位像素）
		NULL,						// 父窗口句柄
		NULL,						// 菜单窗口句柄
		hInstance,					// 应用实例句柄
		this						// 额外参数，挺复杂的
	);

	if (!handle)
		throw;

	this->OnStart();

	ShowWindow(handle, nCmdShow);	// 显示窗口
	UpdateWindow(handle);			// 更新窗口（让系统把这个窗口画出来）
	SetForegroundWindow(handle);
	SetFocus(handle);
	return true;
}

bool Window::ProcessMessage() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	// 从消息队列中获取消息
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_NULL) {
		if (!IsWindow(handle)) {
			return false;
		}
	}
	if (!handle) {
		return false;
	}
	return true;
}

LRESULT CALLBACK Window::HandleMessageSetUp(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_NCCREATE: {
		const CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		// 获取lParam的信息中的window类型的信息
		Window* window = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		if (!window) {
			throw;
		}
		SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageRedirect));
		return DefWindowProc(handle, uMsg, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(handle, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK Window::HandleMessageRedirect(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	return window->WinProc(handle, uMsg, wParam, lParam);
}

LRESULT CALLBACK Window::WinProc(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int result;
	switch (uMsg) {
	case WM_CLOSE:
		result = DestroyWindow(handle);
		this->handle = 0;
		this->OnClose();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:	// 键盘点击
		renderer->WhenKeyPress((int)wParam);
		return 0;
	case WM_KEYUP:		// 键盘松开
		renderer->WhenKeyLoose((int)wParam);
		return 0;
	case WM_LBUTTONDOWN:// 左键点击
		renderer->WhenMouseClick(WM_LBUTTONDOWN);
		return 0;
	case WM_MBUTTONDOWN:// 中键点击
		renderer->WhenMouseClick(WM_MBUTTONDOWN);
		return 0;
	case WM_RBUTTONDOWN:// 右键点击
		renderer->WhenMouseClick(WM_RBUTTONDOWN);
		return 0;
	case WM_LBUTTONUP:	// 左键松开
		renderer->WhenMouseLoose(WM_LBUTTONUP);
		return 0;
	case WM_MBUTTONUP:	// 中键松开
		renderer->WhenMouseLoose(WM_MBUTTONUP);
		return 0;
	case WM_RBUTTONUP:	// 右键松开
		renderer->WhenMouseLoose(WM_RBUTTONUP);
		return 0;
	case WM_MOUSEMOVE:
		renderer->WhenMouseMove(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_SIZE:
		RECT rect;
		GetClientRect(handle, &rect);
		renderer->Resize(rect.right - rect.left, rect.bottom - rect.top);
		return 0;
	default:
		return DefWindowProc(handle, uMsg, wParam, lParam);
	}
}

void Window::PopMessageBox(STRING content, STRING title, UINT uType) {
	MessageBoxEx(handle, content.c_str(), title.c_str(), uType, 0);
}

void Window::Close() {
	PostMessage(handle, WM_CLOSE, 0, 0);
}

void Window::Render() {
	renderer->Render();
}

void Window::OnStart() {
	if (renderer)
		delete renderer;
	renderer = nullptr;
	renderer = new Renderer(handle, width, height);
}

void Window::OnClose() {
	if (renderer)
		delete renderer;
	renderer = nullptr;
}