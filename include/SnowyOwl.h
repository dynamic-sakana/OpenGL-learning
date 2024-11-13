#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <string>

// 请使用此文件的宏定义处理字符串，这会自动处理字符集的问题
// 使用STRING而非std::string或者std::wstring
// 使用CONTEXT()包裹字符串字面量

#ifdef UNICODE

#define STRING std::wstring
#define CONTEXT(a) L##a
#define TOSTRING std::to_wstring

#else

#define STRING std::string
#define CONTEXT(a) a
#define TOSTRING std::to_string

#endif

#include "Renderer.h"
#include "Window.h"