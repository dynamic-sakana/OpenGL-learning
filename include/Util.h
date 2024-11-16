/**
 * @file Util.h
 * @brief 这个文件中有Util类，有很多实用的静态函数，还有一个Image结构体，用于储存图片信息
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "SnowyOwl.h"

struct Image {	
	int width = 0;					// width存储图片的宽
	int height = 0;					// height储存图片的高
	int channel = 0;				// channel储存图片的通道数
	unsigned char* data = nullptr;	// 储存图片主要信息

	/**
	 * @brief 从地址为url的文件中读取图片，读取出来的文件格式为RGBA格式，并且自带反转y轴
	 * @param url 文件地址地址
	 */
	Image(const char* url);
	~Image();
};

/**
 * @brief 这是一个小工具类，有很多使用的小函数
 */
class Util {
public:

	/**
	 * @brief 以二进制的形式读取文件中的所有内容
	 *
	 * @param url 该文件的地址
	 * @return char* 该文件的内容
	 */
	static char* LoadFileContent(const char* url);

	/**
	 * @brief 产生一个指定类型的OpenGL缓冲，并将传入的CPU数据复制到GPU缓冲中，最后将这个缓冲解绑
	 * @param target 指定OpenGL缓冲的类型，如GL_ARRAY_BUFFER
	 * @param size 指定CPU端数据流的长度
	 * @param data CPU端的数据流
	 * @param usage 该缓冲的用途，如GL_STATIC_DRAW
	 * @return GLuint 返回该OpenGL缓冲的标识符
	 */
	static GLuint CreateGLBuffer(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
};
