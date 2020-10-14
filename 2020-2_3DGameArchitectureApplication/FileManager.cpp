#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844


FileManager& FileManager::GetInstance()
{
	static FileManager* _instance;
	
	return *_instance;
}

bool FileManager::LoadObj(
	const char* path,
	std::vector<glm::vec3>& out_vertexes,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	printf("Loading OBJ file: %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}


	while (true)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		out_vertexes.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}

	fclose(file);
	printf("%s file loading has completed.\n", path);
	return true;
}

bool FileManager::LoadObjAdvanced(
	const char* path,
	std::vector<glm::vec3>& out_vertexes,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	std::vector<unsigned int> i_vertex;
	std::vector<unsigned int> i_uv;
	std::vector<unsigned int> i_normal;
	std::vector<glm::vec3> temp_vertex;
	std::vector<glm::vec2> temp_uv;
	std::vector<glm::vec3> temp_normal;

	std::ifstream fileStream(path, std::ios::in);

	if (fileStream.is_open())
	{
		std::string str_line;

		int v_index = 0;
		int f_index = 0;


		while (!fileStream.eof())
		{
			getline(fileStream, str_line);


			if (str_line[0] == 'v')
			{
				if (str_line[1] == ' ')
				{
					glm::vec3 _vertex;

					sscanf_s(str_line.c_str(), "%*s%f %f %f", &_vertex.x, &_vertex.y, &_vertex.z);

					temp_vertex.push_back(_vertex);
				}
				else if (str_line[1] == 't')
				{
					glm::vec2 _uv;

					sscanf_s(str_line.c_str(), "%*s%f %f", &_uv.x, &_uv.y);
					_uv.y = 1 - _uv.y;

					temp_uv.push_back(_uv);
				}
				else if (str_line[1] == 'n')
				{
					glm::vec3 _normal;

					sscanf_s(str_line.c_str(), "%*s%f %f %f", &_normal.x, &_normal.y, &_normal.z);

					temp_normal.push_back(_normal);
				}
			}
			else if (str_line[0] == 'f' && str_line[1] == ' ')
			{
				int _offset = 0;
				int _blockNum = 1;	// "f " 문자가 있으면 최소한 1개의 block("%d/%d/%d")이 있으므로 1을 기본값으로 합니다.

				while ((_offset = str_line.find("//", _offset)) != EOF)
				{
					str_line.insert(_offset + 1, "0");
				}

				_offset = 2;		// "f " 2개의 문자를 건너 뛴 다음부터 검색
				while ((_offset = str_line.find(' ', _offset + 1)) != EOF)
				{
					_blockNum++;
				}


				if (_blockNum == 3)
				{
					int _iv[3], _it[3], _in[3];

					sscanf_s(str_line.c_str(), "%*s%d/%d/%d %d/%d/%d %d/%d/%d", &_iv[0], &_it[0], &_in[0], &_iv[1], &_it[1], &_in[1], &_iv[2], &_it[2], &_in[2]);


					for (int i = 0; i < 3; i++)
					{
						i_vertex.push_back(_iv[i]);
						i_uv.push_back(_it[i]);
						i_normal.push_back(_in[i]);
					}
				}
				else if (_blockNum == 4)
				{
					int _iv[4], _it[4], _in[4];

					sscanf_s(str_line.c_str(), "%*s%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
						&_iv[0], &_it[0], &_in[0], &_iv[1], &_it[1], &_in[1], &_iv[2], &_it[2], &_in[2], &_iv[3], &_it[3], &_in[3]);


					i_vertex.push_back(_iv[0]);
					i_vertex.push_back(_iv[1]);
					i_vertex.push_back(_iv[2]);
					i_uv.push_back(_it[0]);
					i_uv.push_back(_it[1]);
					i_uv.push_back(_it[2]);
					i_normal.push_back(_in[0]);
					i_normal.push_back(_in[1]);
					i_normal.push_back(_in[2]);

					i_vertex.push_back(_iv[0]);
					i_vertex.push_back(_iv[2]);
					i_vertex.push_back(_iv[3]);
					i_uv.push_back(_it[0]);
					i_uv.push_back(_it[2]);
					i_uv.push_back(_it[3]);
					i_normal.push_back(_in[0]);
					i_normal.push_back(_in[2]);
					i_normal.push_back(_in[3]);
				}
				else
				{
					int _iv[3], _it[3], _in[3];

					_offset = 0;
					int _target = 2;


					_target = str_line.find(' ', _target + 1);
					_target = str_line.find(' ', _target + 1);
					_target = str_line.find(' ', _target + 1);
					sscanf_s(str_line.substr(_offset, _target - _offset).c_str(), "%*s%d/%d/%d %d/%d/%d %d/%d/%d",
						&_iv[0], &_it[0], &_in[0], &_iv[1], &_it[1], &_in[1], &_iv[2], &_it[2], &_in[2]);
					_offset = _target;

					for (int i = 0; i < 3; i++)
					{
						i_vertex.push_back(_iv[i]);
						i_uv.push_back(_it[i]);
						i_normal.push_back(_in[i]);
					}


					for (int repeat = 0; repeat < _blockNum - 3; repeat++)
					{
						_iv[1] = _iv[2];
						_it[1] = _it[2];
						_in[1] = _in[2];
						_target = str_line.find(' ', _target + 1);
						sscanf_s(str_line.substr(_offset, _target - _offset).c_str(), "%d/%d/%d", &_iv[2], &_it[2], &_in[2]);
						_offset = _target;

						for (int i = 0; i < 3; i++)
						{
							i_vertex.push_back(_iv[i]);
							i_uv.push_back(_it[i]);
							i_normal.push_back(_in[i]);
						}
					}
				}
			}

			str_line.clear();
		}
	}
	fileStream.close();


	for (unsigned int i = 0; i < i_vertex.size(); i++)
	{
		out_vertexes.push_back(temp_vertex[i_vertex[i] - 1]);
		out_uvs.push_back(temp_uv[i_uv[i] - 1]);
		out_normals.push_back(temp_normal[i_normal[i] - 1]);
	}

	return true;
}

GLuint FileManager::LoadDDS(const char* path)
{
	unsigned char header[124];
	FILE* fp;

	printf("Loading Texture file: %s...\n", path);
	
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
	{
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", path);
		getchar();
		return 0;
	}

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0)
	{
		fclose(fp);
		return 0;
	}

	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char* buffer;
	unsigned int bufsize;
	
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1)
		{
			width = 1;
		}
		if (height < 1)
		{
			height = 1;
		}
	}

	free(buffer);
	printf("%s file loading has completed.\n", path);
	return textureID;
}

GLuint FileManager::LoadShader(const char* vs_path, const char* fs_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vs_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vs_path);
		getchar();
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fs_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile vs
	printf("Compiling shader : %s\n", vs_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fs
	printf("Compiling shader : %s\n", fs_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}