#pragma once

#include "tests.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace tests {

	class TestTexture2D :
		public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;
	private:
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexArray> m_vertexArray;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
	};

}