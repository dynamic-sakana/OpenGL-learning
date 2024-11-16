#include "Texture2D.h"
#include "Util.h"
Texture2D::Texture2D(const char* url) {
	CALL(glGenTextures(1, &textId));
	CALL(glBindTexture(GL_TEXTURE_2D, textId));
	// 设置环绕方式
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	// 设置过滤方式
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	Image text(url);

	this->width = text.width;
	this->height = text.height;
	this->channel = text.channel;

	CALL(glTexImage2D(
		GL_TEXTURE_2D,	// 纹理类型
		0,				// mipmap等级
		GL_RGBA, 		// 纹理的格式
		text.width,		// 图片的宽
		text.height,	// 图片的高
		0,				// 历史遗留，只填0
		GL_RGBA,		// 数据的格式
		GL_UNSIGNED_BYTE,// 数据类型
		text.data		// 图片数据
	));

	CALL(glGenerateMipmap(GL_TEXTURE_2D));
	CALL(glBindTexture(GL_TEXTURE_2D, 0));
}