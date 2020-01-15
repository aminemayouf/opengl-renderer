#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_rendererId));
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_rendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.Elements();
	unsigned offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.Stride(), (const void*)offset));
		offset += element.count * VertexBufferElement::SizeOf(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_rendererId));
}

void VertexArray::Unbind() const
{
	GLCALL(glBindVertexArray(0));
}
