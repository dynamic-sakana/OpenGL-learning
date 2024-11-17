#pragma once
#include "SnowyOwl.h"
#include <istream>

struct Vertex {
	float position[3];
	float normal[3];
	float texcoord[2];
};

class Mesh
{
public:
	Mesh(const char* url);
	~Mesh();
	uint32_t indexCount;
	uint32_t* indices;
	uint32_t vertexCount;
	Vertex* vertices;
	uint32_t faceCount;
};

/**
 * @brief 顶点属性
 */
struct VertexAttri {
	float x, y, z;
};

/**
 * @brief 面的信息，第一个存储位置索引，第二个存储贴图信息索引，第三个存储法线信息索引
 */
struct VertexIndex {
	int posIndex, textureIndex, normalIndex;
};