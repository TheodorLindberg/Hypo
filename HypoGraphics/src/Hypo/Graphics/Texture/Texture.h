#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Texture/TextureAsset.h"

namespace Hypo
{
	enum class TextureUsage
	{
		Static = 0,
		Stream = 1,
		Default = Static
	};
	
	class Texture
	{
	public:
		using Ptr = ObjPtr<Texture>;
		
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(gsl::span<const Byte> pixels) = 0;

		virtual void Bind(uint32_t slot = 0) = 0;
	};

	class HYPO_GRAPHICS_API Texture2D : public Texture
	{
	public:
		using Ptr = ObjPtr<Texture2D>;

		static ObjPtr<Texture2D> Create(TextureData& data, TextureUsage usage = TextureUsage::Static);
	};
}