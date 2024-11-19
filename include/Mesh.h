#pragma once
#include "SnowyOwl.h"
#include <istream>

struct Vertex {
	float position[3];	// 顶点坐标
	float normal[3];	// 顶点坐标对应的法线信息
	float texcoord[2];	// 材质采样坐标
};

/**
 * @brief 网格类，通常来说，在将网格类中的数据存储到GPU端之后，就可以将网格类删除
 */
class Mesh
{
public:
	Mesh(const char* url);
	~Mesh();
	uint32_t indexCount;
	uint32_t* indices;	// 这就是要传给EBO的数据：顶点索引
	uint32_t vertexCount;
	Vertex* vertices;	// 这就是要传给VBO的数据：顶点属性
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