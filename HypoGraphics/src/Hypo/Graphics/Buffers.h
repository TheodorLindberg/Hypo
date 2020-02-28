#pragma once
#include "Hypo/Graphics/Exports.h"
#include "gsl/gsl"

namespace Hypo
{

	template<typename T>
	inline gsl::span<Hypo::Byte> ConvertSpanToBytes(gsl::span<T>& span)
	{
		return gsl::span<Byte>(reinterpret_cast<Hypo::Byte*>(span.data()), span.size_bytes());
	}
	void HYPO_GRAPHICS_API init(void*);
	
	class HYPO_GRAPHICS_API VertexBuffer
	{
	public:
		using Ptr = std::shared_ptr<VertexBuffer>;
		static Ptr Create(gsl::span<float> data, bool dynamic = false);
		static Ptr Create(unsigned int size, bool dynamic = false);

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual void Update(gsl::span<float>, uInt32 offset) = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		
	};

	using ElementIndex = uInt32;

	class HYPO_GRAPHICS_API IndexBuffer
	{
	public:
		using Ptr = std::shared_ptr<IndexBuffer>;
		static Ptr Create(gsl::span<ElementIndex> data, bool dynamic = false);
		static Ptr Create(unsigned int size, bool dynamic = false);

		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void Update(gsl::span<ElementIndex> data, uInt32 offset) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

}
