	#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "gsl/gsl"
#include "Hypo/Graphics/Shader/Shader.h"

	namespace Hypo
{

	template<typename T>
	inline gsl::span<Byte> ConvertSpanToBytes(gsl::span<T>& span)
	{
		return gsl::span<Byte>(reinterpret_cast<Byte*>(span.data()), span.size_bytes());
	}
	void HYPO_GRAPHICS_API init(void*);
	
	class HYPO_GRAPHICS_API VertexBuffer
	{
	public:
		using Ptr = ObjPtr<VertexBuffer>;
		static Ptr Create(gsl::span<float> data, bool dynamic = false);
		static Ptr Create(unsigned int size, bool dynamic = false);

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual void Update(gsl::span<float>, uInt32 offset) = 0;
		
		virtual BufferLayout GetLayout() = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		
	};

	using ElementIndex = uInt32;

	class HYPO_GRAPHICS_API IndexBuffer
	{
	public:
		using Ptr = ObjPtr<IndexBuffer>;
		static Ptr Create(gsl::span<ElementIndex> data, bool dynamic = false);
		static Ptr Create(unsigned int size, bool dynamic = false);

		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void Update(gsl::span<ElementIndex> data, uInt32 offset) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class HYPO_GRAPHICS_API VertexArray
	{
	public:
		using Ptr = ObjPtr<VertexArray>;
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer::Ptr buffer, Shader::Ptr shader) = 0;
		virtual void SetIndexBuffer(IndexBuffer::Ptr buffer) = 0;
		virtual IndexBuffer::Ptr GetIndexBuffer() const = 0;
		static Ptr Create();
	};
}
