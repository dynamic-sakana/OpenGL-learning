#include "SnowyOwl.h"
using namespace SnowyOwl;
#include "Log.h"
#include "Window.h"
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
#endif
	Window window(hInstance, CONTEXT("windows  class"));
	window.Initialize(CONTEXT("Snowy Owl引擎"), 800, 800, nCmdShow);

	while (window.ProcessMessage()) {
		window.Render();
		Sleep(10);
	}
	
	return 0;
}