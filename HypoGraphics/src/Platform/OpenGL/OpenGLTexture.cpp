#include "graphicspch.h"
#include "OpenGLTexture.h"
#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"
#include "Platform/OpenGL/OpenGLError.h"

Hypo::OpenGLTexture2D::OpenGLTexture2D(TextureData data)
	:m_TextureData(data)
{


	int channelCode = 0;

	switch (data.GetType())
	{
	case TextureType::Rgb: channelCode = GL_RGB;  break;
	case TextureType::Rgba: channelCode = GL_RGBA; break;
	default: HYPO_CORE_WARN("[Texture] Texture type not suported!, Channel count: {}", static_cast<int>(data.GetType()));
	}
	
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);


	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, channelCode, data.GetWidth(), data.GetHeight(), 0, channelCode, GL_UNSIGNED_BYTE, data.GetPixels().data()));
	
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
}

Hypo::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Hypo::OpenGLTexture2D::SetData(gsl::span<Byte> pixels)
{

	int channelCode = 0;

	switch (m_TextureData.GetType())
	{
	case TextureType::Rgb: channelCode = GL_RGB;  break;
	case TextureType::Rgba: channelCode = GL_RGBA; break;
	default: HYPO_CORE_WARN("[Texture] Texture type not suported!, Channel count: {}", static_cast<int>(m_TextureData.GetType()));
	}
	
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	HYPO_CORE_ASSERT(pixels.size() == m_TextureData.GetPixelsSize(), "Data must be entire texture!");
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.GetWidth(), m_TextureData.GetHeight(), channelCode, GL_UNSIGNED_BYTE, pixels.data());
}

void Hypo::OpenGLTexture2D::Bind(uint32_t slot)
{
	m_BoundSlot = slot;
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	
	glBindTextureUnit(slot, m_RendererID);
}
