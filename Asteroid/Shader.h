#pragma once

#include <GL/glew.h>
#include "Math.h"
#include <string>

class Shader {
public:
	Shader();
	~Shader();

	bool Load(const std::string& vertName,
		const std::string& fragName);

	void Unload();

	void SetActive();

	void SetVectorUniform(const char* name, const Vector3& vector);

	void SetMatrixUniform(const char* name,const Matrix4& maxtrix);

	void SetMatrixUniforms(const char* name, Matrix4* maxtrix ,unsigned size);

	void SetFloatUniform(const char* name, float value);
private:
	bool CompileShader(const std::string& fileName,
		GLenum shaderType, GLuint& outShader);

	bool IsCompiled(GLuint shader);

	bool IsValidProgram();

	GLuint mVertexShader;

	GLuint mFragShader;

	GLuint mShaderProgram;
};
