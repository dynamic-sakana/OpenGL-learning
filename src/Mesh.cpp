#include "Mesh.h"
#include "Util.h"
#include <sstream>
#include <vector>
Mesh::Mesh(const char* url) {
	char* data = Util::LoadFileContent(url);
	if (!data) {
		throw;
	}
	std::stringstream strStream(data);
	delete[] data;

	std::vector<VertexAttri> position, normal, texture;
	std::vector<VertexIndex> vertices;
	std::vector<uint32_t> indices;
	const int MAX_SIZE = 256;
	char line[MAX_SIZE];
	while (!strStream.eof()) {
		strStream.getline(line, MAX_SIZE);
		std::stringstream lineStream(line);
		VertexAttri vert;
		std::string temp;
		switch (line[0]) {
		case 'v':	// 表示顶点的某些属性
			switch (line[1]) {
			case 't':	// 前两个字符为“vt”表示贴图坐标
				lineStream >> temp;
				lineStream >> vert.x;
				lineStream >> vert.y;
				lineStream >> vert.z;
				texture.push_back(vert);
			case 'n':	// 前两个字符为“vn”表示法线
				lineStream >> temp;
				lineStream >> vert.x;
				lineStream >> vert.y;
				lineStream >> vert.z;
				normal.push_back(vert);
			default:	// 第一个字符为“v”表示顶点坐标
				lineStream >> temp;
				lineStream >> vert.x;
				lineStream >> vert.y;
				lineStream >> vert.z;
				position.push_back(vert);
			}
		case 'f':	// 表示面
			lineStream >> temp;
			for (int i = 0; i < 3; i++) {
				lineStream >> temp;
				int pos1 = temp.find_first_of('/');
				std::string vStr = temp.substr(0, pos1);

				int pos2 = temp.find_first_of('/', pos1 + 1);
				std::string tStr = temp.substr(pos1 + 1, pos2 - pos1 - 1);

				std::string nStr = temp.substr(pos2 + 1, temp.length() - pos2 - 1);

				VertexIndex vi;
				vi.posIndex = atoi(vStr.c_str()) - 1;
				vi.textureIndex = atoi(tStr.c_str()) - 1;
				vi.normalIndex = atoi(nStr.c_str()) - 1;

				int index = -1;
				int currentVertexCount = vertices.size();
				// 重复性检查
				for (int k = 0; k < currentVertexCount; k++) {
					if (vertices[k].posIndex == vi.posIndex&&
						vertices[k].textureIndex == vi.textureIndex&&
						vertices[k].normalIndex == vi.normalIndex) {
						index = k;
						break;
					}
				}
				if (index == -1) {
					index = vertices.size();
					vertices.push_back(vi);
				}
				indices.push_back(index);
			}
		}
	}
	this->indexCount = indices.size();
	this->indices = new uint32_t[indexCount];
	memcpy(this->indices, &indices[0], indexCount * sizeof(uint32_t));
	this->vertexCount = vertices.size();
	this->vertices = new Vertex[this->vertexCount];
	for (int i = 0; i < this->vertexCount; i++) {
		memcpy(&this->vertices[i].position, &position[vertices[i].posIndex], sizeof(float) * 3);
		memcpy(&this->vertices[i].normal, &normal[vertices[i].normalIndex], sizeof(float) * 3);
		memcpy(&this->vertices[i].texcoord, &texture[vertices[i].textureIndex], sizeof(float) * 2);
	}
	this->faceCount = this->indexCount / 3;
}