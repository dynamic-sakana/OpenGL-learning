#pragma once
#include "SnowyOwl.h"
class Texture2D {
public:
	Texture2D(const char* url);
	~Texture2D();
public:
	GLuint textId;
	int width, height, channel;
};