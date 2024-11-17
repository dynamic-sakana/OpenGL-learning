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

void Model::SetShader(ShaderProgram* shader) {
	this->shader = shader;
	CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	shader->ParseVBOData("pos", 3, GL_FLOAT, false, 8 * sizeof(float), 0);
	shader->ParseVBOData("color", 3, GL_FLOAT, false, 8 * sizeof(float), 3 * sizeof(float));
	shader->ParseVBOData("uv", 2, GL_FLOAT, false, 8 * sizeof(float), 6 * sizeof(float));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Model::SetTexture(const char* name, Texture2D* texture) {
	shader->Apply();
	shader->SetTexture(name, texture);
	shader->Stop();
}

void Model::Translate(float x, float y, float z) { modelMat = glm::translate(modelMat, glm::vec3(x, y, z)); }

void Model::Translate(const glm::vec3& displacement) { modelMat = glm::translate(modelMat, displacement); }

void Model::Rotate(float angle, float x, float y, float z) { modelMat = glm::rotate(modelMat, angle, glm::vec3(x, y, z)); }

void Model::Rotate(float angle, const glm::vec3& axis) { modelMat = glm::rotate(modelMat, angle, axis); }

void Model::Scale(float x, float y, float z) { modelMat = glm::scale(modelMat, glm::vec3(x, y, z)); }

void Model::Scale(const glm::vec3& resize) { modelMat = glm::scale(modelMat, resize); }

void Model::Draw(const glm::mat4& viewMat, const glm::mat4& projMat) {
	shader->Apply();
	shader->SetUniformM4("modelMat", false, modelMat);
	shader->SetUniformM4("viewMat", false, viewMat);
	shader->SetUniformM4("projMat", false, projMat);
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	shader->Stop();
}
