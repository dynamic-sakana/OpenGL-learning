#include "Util.h"

// 避免重定义
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_master/stb_image.h>

Image::Image(const char* url) {
	stbi_set_flip_vertically_on_load(true);	// 反转y轴
	data = stbi_load(url, &width, &height, &channel, STBI_rgb_alpha);
	ERROR_LOG("Fail to load image.");
}

Image::~Image() {
	stbi_image_free(data);
}

char* Util::LoadFileContent(const char* url) {
	char* content = nullptr;
	FILE* fp = fopen(url, "rb");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		if (len > 0) {
			rewind(fp);
			content = new char[len + 1];
			fread(content, 1, len, fp);
			content[len] = '\0';
		}
		fclose(fp);

	}
	else {
		std::string error("Fail to access file: ");
		MessageBoxA(0, error.append(url).c_str(), "Error", MB_OK | MB_ICONERROR);
	}
	return content;
}

GLuint Util::CreateGLBuffer(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
	GLuint bufferId;
	CALL(glGenBuffers(1, &bufferId));				// 创建一个缓冲
	CALL(glBindBuffer(target, bufferId));			// 绑定创建的缓冲
	CALL(glBufferData(target, size, data, usage));	// 将CPU端的数据发往GPU端
	CALL(glBindBuffer(target, 0));					// 解绑该缓冲
	return bufferId;
}


