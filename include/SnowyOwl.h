#pragma once

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

#include <GL/glew.h>
#include <Windows.h>
#include <string>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// 如果当前在DEBUG模式，那么就会检查函数调用是否成功
// 并且会获取errorCode和error说明
#ifdef __DEBUG__
namespace SnowyOwl {
	static int errorCode = 0;		// 用于OpenGL中的错误处理
	static std::string error = "";	// 用于其他情况下的的错误处理，比如窗口注册失败等等
}
#define ERROR_LOG(x) SnowyOwl::error=x
#define CALL(x) x;assert(!(SnowyOwl::errorCode = glGetError()))
#else
#define CALL(x) x
#define ERROR_LOG(x)
#endif