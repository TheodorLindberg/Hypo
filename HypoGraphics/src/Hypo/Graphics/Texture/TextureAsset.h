#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "Hypo/Window/Context/GraphicsContext.h"
#include <gsl/span>

namespace Hypo
{


	enum class TextureType
	{
		None,
		Rgb,
		Rgba,
		sRgb,
		sRgba,
		Stencil,
		Depth
	};

	HYPO_GRAPHICS_API uInt32 GetTexturePixelSize(TextureType type);
	HYPO_GRAPHICS_API uInt32 GetTextureSize(uInt32 width, uInt32 height, TextureType type);

	class TextureData
	{
	public:
		TextureData(uInt32 width, uInt32 height, TextureType type);

		TextureData(uInt32 width, uInt32 height, TextureType type, std::vector<Byte> pixels);

		TextureData() = default;
		TextureData(const TextureData&) = default;

		uInt32 GetWidth() const { return m_Width; }
		uInt32 GetHeight() const { return m_Height; }
		TextureType GetType()const { return m_Type; }
		uInt32 GetPixelsSize() const { return m_Pixels.size(); }
		const std::vector<Byte>& GetPixels() const { return m_Pixels; }
	private:
		uInt32 m_Width = 0;
		uInt32 m_Height = 0;
		TextureType m_Type = TextureType::None;
		std::vector<Byte> m_Pixels;
	};

	HYPO_GRAPHICS_API TextureData TextureFromFile(std::string path);
}






