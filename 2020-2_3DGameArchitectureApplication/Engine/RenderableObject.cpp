#include "RenderableObject.h"
#include "FileManager.h"
#include "Renderer.h"

#include <iostream>


RenderableObject::RenderableObject(std::string object_name) : CompositeObject(object_name)
{
	_vertexArrayID = 0;
	_programID = 0;
	_matrixID = 0;
	_viewMatrixID = 0;
	_modelMatrixID = 0;
	_textureID = 0;
	_lightID = 0;

	_projectionMatrix = glm::mat4(1.0f);
	_viewMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::mat4(1.0f);
	_MVP = glm::mat4(1.0f);
	
	_vertexes.clear();
	_uvs.clear();
	_normals.clear();

	_texture = 0;

	_vertexBuffer = 0;
	_uvBuffer = 0;
	_normalBuffer = 0;

	_relativeLightPos = new std::vector<glm::vec3>();

	_isInitialized = false;
}

void RenderableObject::Initialize(const char* obj_file_path, const char* dds_file_path, const char* vs_path, const char* fs_path)
{
	// obj 파일 로드
	FileManager::GetInstance().LoadObj(obj_file_path, _vertexes, _uvs, _normals);


	// dds 파일 로드
	_texture = FileManager::GetInstance().LoadDDS(dds_file_path);


	// obj 정점 정보 바인드
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertexes.size() * sizeof(glm::vec3), &_vertexes[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);

	// 쉐이더 로딩 및 바인드
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	_programID = FileManager::GetInstance().LoadShader(vs_path, fs_path);

	_matrixID = glGetUniformLocation(_programID, "MVP");
	_viewMatrixID = glGetUniformLocation(_programID, "V");
	_modelMatrixID = glGetUniformLocation(_programID, "M");

	_textureID = glGetUniformLocation(_programID, "myTextureSampler");

	_lightID = glGetUniformLocation(_programID, "LightPosition_worldspace");

	_isInitialized = true;
}


void RenderableObject::Init()
{
	CompositeObject::Init();
	
	if (!_isInitialized)
	{
		std::cout << "ERROR: " << GetName() << " is not initialized." << std::endl;
	}
}

void RenderableObject::Update()
{
	CompositeObject::Update();
}

void RenderableObject::Render()
{
	if (_isInitialized)
	{
		glm::mat4 model_translate = glm::translate(glm::mat4(1.0f), GetObjectLocation());
		glm::mat4 model_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(GetObjectRotationDegree()), GetObjectRotationAxis());
		glm::mat4 model_scale = glm::scale(glm::mat4(1.0f), GetObjectScale());
		glm::mat4 model_parentRot = glm::mat4(1.0f);
		glm::mat4 model_parentPos = glm::mat4(1.0f);

		if (IsChild())
		{
			model_parentRot = glm::rotate(glm::mat4(1.0f), glm::radians(GetParent()->GetObjectRotationDegree()), GetParent()->GetObjectRotationAxis());
			model_parentPos = glm::translate(glm::mat4(1.0f), GetParent()->GetObjectLocation());
		}

		_MVP = _projectionMatrix * _viewMatrix * model_parentPos * model_parentRot * model_translate * model_rotate * model_scale * _modelMatrix;


		glUseProgram(_programID);

		glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_MVP[0][0]);
		glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &_modelMatrix[0][0]);
		glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &_viewMatrix[0][0]);



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GetTexture());
		glUniform1i(_textureID, 0);


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, GetVertexBuffer());
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, GetUVBuffer());
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, GetNormalBuffer());
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);


		glDrawArrays(GL_TRIANGLES, 0, GetVertexSize());


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

void RenderableObject::OnCollision(BoxCollider* other)
{
	CompositeObject::OnCollision(other);
}


void RenderableObject::SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	_modelMatrix = model;
	_viewMatrix = view;
	_projectionMatrix = projection;
}

void RenderableObject::UniformShaderRelativeLightPos(glm::vec3 light_worldPos)
{
	glm::mat4 reverse_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(GetObjectRotationDegree() * -1.0f), GetObjectRotationAxis());
	glm::mat4 model_parentPos = glm::mat4(1.0f);
	glm::mat4 model_parentRot = glm::mat4(1.0f);

	int count = 0;
	glm::vec4 model_worldPos_v4 = glm::vec4(GetObjectLocation(), 1.0f);
	Object* generation = this;
	while (generation->IsChild())
	{
		generation = generation->GetParent();
		model_parentRot = glm::rotate(glm::mat4(1.0f), glm::radians(generation->GetObjectRotationDegree()), generation->GetObjectRotationAxis());
		model_parentPos = glm::translate(glm::mat4(1.0f), generation->GetObjectLocation());
		model_worldPos_v4 = model_parentPos * model_parentRot * model_worldPos_v4;
		count++;
	}
	if (count >= 2)
	{
		reverse_rotate = glm::mat4(1.0f);
	}

	glm::vec3 model_worldPos = glm::vec3(model_worldPos_v4.x, model_worldPos_v4.y, model_worldPos_v4.z);
	glm::vec3 light_worldPos_scaledDist = glm::vec3(
		light_worldPos.x - (glm::abs(model_worldPos.x) - (GetObjectScale().x)) * ((model_worldPos.x > 0) - (model_worldPos.x < 0)),
		light_worldPos.y - (glm::abs(model_worldPos.y) - (GetObjectScale().y)) * ((model_worldPos.y > 0) - (model_worldPos.y < 0)),
		light_worldPos.z - (glm::abs(model_worldPos.z) - (GetObjectScale().z)) * ((model_worldPos.z > 0) - (model_worldPos.z < 0)));
	glm::vec4 light_relativePos = reverse_rotate * glm::vec4(light_worldPos_scaledDist, 1.0f);

	glUseProgram(_programID);
	glUniform3f(_lightID, light_relativePos.x, light_relativePos.y, light_relativePos.z);
}


GLuint RenderableObject::GetTexture() const
{
	return _texture;
}

GLuint RenderableObject::GetVertexBuffer() const
{
	return _vertexBuffer;
}
GLuint RenderableObject::GetUVBuffer() const
{
	return _uvBuffer;
}
GLuint RenderableObject::GetNormalBuffer() const
{
	return _normalBuffer;
}

size_t RenderableObject::GetVertexSize() const
{
	return _vertexes.size();
}

void RenderableObject::ReleaseMemory()
{
	CompositeObject::ReleaseMemory();
	
	glDeleteProgram(_programID);
	glDeleteVertexArrays(1, &_vertexArrayID);
	
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteTextures(1, &_texture);

	_vertexes.clear();
	_uvs.clear();
	_normals.clear();

	_relativeLightPos->clear();
	delete _relativeLightPos;

	delete this;
}