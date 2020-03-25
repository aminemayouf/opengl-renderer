#pragma once

#include "glm/glm.hpp"

#include<string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_filepath;
	unsigned int m_rendererId;
	mutable std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f4);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int Compile(unsigned int type, const std::string& source);
	unsigned int Create(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource Parse(const std::string& filepath);

	int UniformLocation(const std::string& name) const;
};