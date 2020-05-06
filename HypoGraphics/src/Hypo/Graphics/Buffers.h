	#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/System/DataTypes/ObjPtr.h"
#include "gsl/gsl"
#include "Hypo/Graphics/Shader/Shader.h"

namespace Hypo
{
	enum class MeshType;

	template<typename T>
	inline gsl::span<const Byte> ConvertSpanToBytes(gsl::span<const T>& span)
	{
		return gsl::span<const Byte>(reinterpret_cast<const Byte*>(span.data()), span.size_bytes());
	}
	void HYPO_GRAPHICS_API init(void*);

	enum class BufferUsage
	{
		Static = 0,
		Stream = 1,
		Dynamic = 2,
		Default = Static
	};
	
	class HYPO_GRAPHICS_API VertexBuffer
	{
	public:
		using Ptr = ObjPtr<VertexBuffer>;
		static Ptr Create(gsl::span<const float> data, BufferUsage usage = BufferUsage::Default);
		static Ptr Create(unsigned int size, BufferUsage usage = BufferUsage::Default);

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual void Update(gsl::span<const float>, uInt32 offset) = 0;
		
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
		static Ptr Create(gsl::span<const ElementIndex> data, BufferUsage usage = BufferUsage::Default);
		static Ptr Create(unsigned int size, BufferUsage usage = BufferUsage::Default);

		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void Update(gsl::span<const ElementIndex> data, uInt32 offset) = 0;

		virtual uInt32 GetCount() const = 0;
		
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
		virtual void AddVertexBuffer(VertexBuffer::Ptr buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer::Ptr buffer) = 0;
		virtual bool HasIndexBuffer() = 0;
		virtual void SetMeshType(MeshType type) = 0;
		virtual MeshType GetMeshType() = 0;
		virtual uInt32 GetIndicesCount() = 0;
		virtual IndexBuffer::Ptr GetIndexBuffer() const = 0;
		static Ptr Create();
	};
}
