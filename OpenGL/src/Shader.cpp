#include "Shader.h"

#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string& filepath)
	: m_filepath(filepath), m_rendererId(0)
{
    ShaderProgramSource source = Parse(filepath);
    m_rendererId = Create(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(m_rendererId));
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(m_rendererId));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

unsigned int Shader::Compile(unsigned int type, const std::string& source)
{
    GLCALL(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << std::endl;
        std::cerr << message << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::Create(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCALL(unsigned int program = glCreateProgram());
    unsigned int vs = Compile(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = Compile(GL_FRAGMENT_SHADER, fragmentShader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}

ShaderProgramSource Shader::Parse(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

void Shader::SetUniform1i(const std::string& name, int v)
{
    GLCALL(glUniform1i(UniformLocation(name), v));
}

void Shader::SetUniform1f(const std::string& name, float v)
{
    GLCALL(glUniform1f(UniformLocation(name), v));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(UniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::UniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLCALL(int location = glGetUniformLocation(m_rendererId, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    else
        m_uniformLocationCache[name] = location;

    return location;
}
