#pragma once
#include "SnowyOwl.h"

namespace SnowyOwl {
	class Renderer;
	class Window {
	public:
		/**
		 * @brief 构造一个Window类
		 * 
		 * @param hInstance 窗口应用实例
		 * @param windows_class 窗口类名字
		 */
		Window(HINSTANCE hInstance, STRING windows_class);

		/**
		 * @brief 析构Window类，取消窗口类的注册
		 * 
		 */
		~Window();

		/**
		 * @brief 初始化并显示窗口
		 * @param windows_title 窗口的标题
		 * @param width 窗口宽度
		 * @param height 窗口高度
		 * @param nCmdShow 显示模式
		 * @return true
		 * @return false
		 */
		bool Initialize(STRING windows_title, int width, int height, int nCmdShow);

		/**
		 * @brief 注册窗口类
		 * @return true 注册成功
		 * @return false 注册失败
		 */
		bool RegisterWindowsClass();

		/**
		 * @brief 窗口接收输入的消息后的处理函数
		 * @return true 窗口正常接收、分发消息
		 * @return false 窗口接收到空消息并且窗口已经不存在时，或者窗口句柄无效时
		 */
		bool ProcessMessage();

		/**
		 * @brief 在此窗口上展示一个消息窗口，和MessageBox是一样的
		 * @param content 弹出窗口的内容
		 * @param title 弹出窗口的标题名称
		 * @param uType 弹出窗口的键类型
		 */
		void PopMessageBox(STRING content, STRING title, UINT uType);

		/**
		 * @brief 关闭此窗口
		 */
		void Close();

		void Render();

		void OnStart();
		void OnClose();

	private:
		static LRESULT CALLBACK HandleMessageSetUp(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMessageRedirect(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WinProc(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND handle;			// 窗口实例句柄
		HINSTANCE hInstance;	// 应用实例句柄
		STRING windowTitle;		// 窗口名称
		STRING windowClass;		// 窗口类名
		int width;	// 窗口宽度
		int height;	// 窗口高度

		Renderer* renderer = nullptr;
	};
}