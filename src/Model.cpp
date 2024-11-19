#include "Model.h"
#include "Mesh.h"
#include "Util.h"
Model::Model(const char* url) {
	Mesh* mesh = new Mesh(url);
	count = mesh->indexCount;
	VBO = Util::CreateGLBuffer(GL_ARRAY_BUFFER, mesh->vertexCount * sizeof(Vertex), mesh->vertices, GL_STATIC_DRAW);
	EBO = Util::CreateGLBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(uint32_t), mesh->indices, GL_STATIC_DRAW);
	modelMat = glm::mat4(1.0f);
	mesh->~Mesh();
}

Model::~Model() {
	CALL(glDeleteBuffers(1, &EBO));
	CALL(glDeleteBuffers(1, &VBO));
}

void Model::SetShader(ShaderProgram* shader) {
	this->shader = shader;
	CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	shader->ParseVBOData("pos", 3, GL_FLOAT, false, 8 * sizeof(float), 0);
	shader->ParseVBOData("normal", 3, GL_FLOAT, false, 8 * sizeof(float), 3 * sizeof(float));
	shader->ParseVBOData("textCoord", 2, GL_FLOAT, false, 8 * sizeof(float), 6 * sizeof(float));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Model::SetTexture(const char* name, Texture2D* texture) {
	for (std::pair<const char*, Texture2D*> pair : texture2DList) {
		if (strcmp(pair.first, name) == 0) {
			// 如果这个采样器采样的纹理已经被设置过了，将纹理对象更新
			pair.second = texture;
			return;
		}
	}
	// 如果这个采样器采样的纹理没有被设置过，设置该采样器的纹理对象
	texture2DList.push_back(std::pair<const char*, Texture2D*>(name, texture));
}

void Model::Translate(float x, float y, float z) {
	modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * modelMat;
}

void Model::Translate(const glm::vec3& displacement) {
	modelMat = glm::translate(glm::mat4(1.0f), displacement) * modelMat;
}

void Model::Move(float x, float y, float z) {
	modelMat = glm::translate(modelMat, glm::vec3(x, y, z));
}

void Model::Move(const glm::vec3& displacement) {
	modelMat = glm::translate(modelMat, displacement);
}

void Model::Revolve(float angle, float x, float y, float z) {
	modelMat = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(glm::vec3(x, y, z))) * modelMat;
}

void Model::Revolve(float angle, const glm::vec3& axis) {
	modelMat = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis)) * modelMat;
}

void Model::Rotate(float angle, float x, float y, float z) {
	modelMat = glm::rotate(modelMat, angle, glm::normalize(glm::vec3(x, y, z)));
}

void Model::Rotate(float angle, const glm::vec3& axis) {
	modelMat = glm::rotate(modelMat, angle, glm::normalize(axis));
}

void Model::Scale(float x, float y, float z) {
	modelMat = glm::scale(modelMat, glm::vec3(x, y, z));
}

void Model::Scale(const glm::vec3& resize) {
	modelMat = glm::scale(modelMat, resize);
}

void Model::Draw(const glm::mat4& viewMat, const glm::mat4& projMat) {
	shader->Apply();
	for (std::pair<const char*, Texture2D*> pair : texture2DList) {
		shader->SetTexture(pair.first, pair.second);
	}
	shader->SetUniformM4("modelMat", false, modelMat);
	shader->SetUniformM4("viewMat", false, viewMat);
	shader->SetUniformM4("projMat", false, projMat);
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	shader->Stop();
}
