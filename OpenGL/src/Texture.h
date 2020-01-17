#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_rendererId;
	std::string m_filepath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int Width() const { return m_width; }
	inline int Height() const { return m_height; }
};
