#include "graphicspch.h"

#include "TextureAsset.h"

#include "Hypo/System/Util/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Hypo::uInt32 Hypo::GetTexturePixelSize(TextureType type)
{
	switch (type)
	{
	case Hypo::TextureType::None:
		return 0;
		break;
	case Hypo::TextureType::Rgb:
		return 3;
		break;
	case Hypo::TextureType::Rgba:
		return 4;
		break;
	case Hypo::TextureType::sRgb:
		return 4;
		break;
	case TextureType::sRgba:
		return 4;
		break;
	case TextureType::Stencil:
		return 1;
		break;
	case TextureType::Depth:
		return 3;
		break;
	default:
		return 0;
		break;
	}
}

Hypo::uInt32 Hypo::GetTextureSize(uInt32 width, uInt32 height, TextureType type)
{
	return GetTexturePixelSize(type) * width * height;
}

Hypo::TextureData::TextureData(uInt32 width, uInt32 height, TextureType type)
	: m_Width(width), m_Height(height), m_Type(type)
{}

Hypo::TextureData::TextureData(uInt32 width, uInt32 height, TextureType type, std::vector<Byte> pixels)
	: m_Width(width),	m_Height( height), m_Type(type), m_Pixels(std::move(pixels))
{}

Hypo::TextureData Hypo::TextureFromFile(std::string path)
{
	int width, height, bpp;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
	if (!data)
	{

		HYPO_CORE_WARN("[Loader] Could not load texture: {}", path);
		return TextureData(0, 0, TextureType::None);
	}

	std::size_t size = width * height * bpp;

	std::vector<Byte> pixels;
	pixels.resize(size);
	
	memcpy(pixels.data(), data, size);

	stbi_image_free(data);

	TextureType type;

	switch (bpp)
	{
	case 3:
		type = TextureType::Rgb;
		break;
	case 4:
		type = TextureType::Rgba;
		break;
	default:
		type = TextureType::None;
		break;
	}

	return TextureData(width, height, type, pixels);

}



//H3kf02lp!