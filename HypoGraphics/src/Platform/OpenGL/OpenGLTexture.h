#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Texture/Texture.h"

namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureData data);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_TextureData.GetWidth(); }
		virtual uint32_t GetHeight() const override { return m_TextureData.GetHeight(); }

		virtual void SetData(gsl::span<Byte> pixels) override;

		virtual void Bind(uint32_t slot = 0) override;

		uInt32 GetRendererID() const { return m_RendererID; }
		uInt32 GetBoundSlot() const { return m_BoundSlot; }
	private:
		TextureData m_TextureData;
		uInt32 m_RendererID;
		uInt32 m_BoundSlot;
	};
}
