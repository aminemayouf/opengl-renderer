#include "TestTexture2D.h"

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

#include <GL/glew.h>

namespace tests {

	TestTexture2D::TestTexture2D()
		: m_projection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_translationA(200, 200, 0), m_translationB(400, 200, 0)
	{
		float positions[] = {
			100.0f,  100.0f, 0.0f, 0.0f, // 0
			200.0f,  100.0f, 1.0f, 0.0f, // 1
			200.0f,  200.0f, 1.0f, 1.0f, // 2
			100.0f,  200.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCALL(glEnable(GL_BLEND));

		m_vertexArray = std::make_unique<VertexArray>();

		m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
		m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_shader->Bind();
		m_shader->SetUniform4f("uColor", 0.8f, 0.3f, 0.8f, 1.0f);
		m_texture = std::make_unique<Texture>("res/textures/snes.png");
		m_shader->SetUniform1i("uTexture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_projection * m_view * model;
			m_shader->Bind();
			m_shader->SetUniformMat4f("uMVP", mvp);

			renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 mvp = m_projection * m_view * model;
			m_shader->Bind();
			m_shader->SetUniformMat4f("uMVP", mvp);

			renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
		}
	}

	void TestTexture2D::OnGUI()
	{
		ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}


